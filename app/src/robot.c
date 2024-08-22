#include "robot.h"

#include "robot_tasks.h"
#include "chassis_task.h"
#include "gimbal_task.h"
#include "launch_task.h"
#include "remote.h"
#include "bsp_can.h"
#include "gimbal_task.h"
#include <math.h>
#include "imu_task.h"
#include "user_math.h"
#include "referee_system.h"
#include "buzzer.h"
#include "ui.h"
#include "user_math.h"
#include "Swerve_Locomotion.h"
#include "supercap.h"

extern DJI_Motor_Handle_t *g_yaw;

#define KEYBOARD_RAMP_COEF (0.004f)
#define SPINTOP_COEF (0.003f)
#define MAX_SPEED (1.0f)

Robot_State_t g_robot_state = {0, 0};
Key_Prev_t g_key_prev = {0};
extern Launch_Target_t g_launch_target;
extern Remote_t g_remote;
extern Supercap_t g_supercap;

uint8_t g_start_safely = 0;

void Robot_Cmd_Loop(void);
void _toggle_robot_state(uint8_t *state);

void Robot_Init()
{
    Buzzer_Init();
    Melody_t system_init_melody = {
        .notes = SYSTEM_INITIALIZING,
        .loudness = 0.5f,
        .note_num = SYSTEM_INITIALIZING_NOTE_NUM,
    };
    Buzzer_Play_Melody(system_init_melody); // TODO: Change to non-blocking

    // Initialize all hardware
    Chassis_Task_Init();
    Gimbal_Task_Init();
    Launch_Task_Init();
    Remote_Init(&huart3);
    CAN_Service_Init();
    Referee_System_Init(&huart1);
    //Jetson_Orin_Init(&huart6);
    Supercap_Init(&g_supercap);
    //   Initialize all tasks
    Robot_Tasks_Start();
}

void Robot_Ctrl_Loop()
{
    // Control loop for the robot
    Robot_Cmd_Loop();
    Referee_Set_Robot_State();
    Chassis_Ctrl_Loop();
    Gimbal_Ctrl_Loop();
    Launch_Ctrl_Loop();
}
/**
 *  B - Flywheel On Off
 *  G - Spin Top Mode
 */
void Robot_Cmd_Loop()
{
    // safely startly will be 1 after first time right switch is down
    // this is to make sure the robot is disabled when it starts
    if (g_robot_state.safely_started == 1)
    {
        if ((g_remote.online_flag == REMOTE_OFFLINE) || (g_remote.controller.right_switch == DOWN))
        {
            g_robot_state.enabled = 0;
            g_launch_target.flywheel_enabled = 0;
        }
        else
        {
            g_robot_state.enabled = 1;

            /* Gimbal starts here */ // (Launch enable in last if statement)
            g_robot_state.vy_keyboard = ((1.0f - KEYBOARD_RAMP_COEF) * g_robot_state.vy_keyboard + g_remote.keyboard.W * KEYBOARD_RAMP_COEF - g_remote.keyboard.S * KEYBOARD_RAMP_COEF);
            g_robot_state.vx_keyboard = ((1.0f - KEYBOARD_RAMP_COEF) * g_robot_state.vx_keyboard - g_remote.keyboard.A * KEYBOARD_RAMP_COEF + g_remote.keyboard.D * KEYBOARD_RAMP_COEF);
            g_robot_state.vx = g_robot_state.vx_keyboard + g_remote.controller.left_stick.x / REMOTE_STICK_MAX;
            g_robot_state.vy = g_robot_state.vy_keyboard + g_remote.controller.left_stick.y / REMOTE_STICK_MAX;
            g_robot_state.vx *= MAX_SPEED;
            g_robot_state.vy *= MAX_SPEED;

            float theta = DJI_Motor_Get_Absolute_Angle(g_yaw);
            g_robot_state.chassis_x_speed = -g_robot_state.vy * sin(theta) + g_robot_state.vx * cos(theta);
            g_robot_state.chassis_y_speed = g_robot_state.vy * cos(theta) + g_robot_state.vx * sin(theta);

            if (g_remote.controller.left_switch == DOWN)
            {
                if (g_key_prev.prev_left_switch != DOWN)
                { // if previous state is not mid change, this allows keyboard to toggle spin top mode
                    g_robot_state.spintop_mode = 0;
                }
            }
            else if (g_remote.controller.left_switch == MID)
            {
                if (g_key_prev.prev_left_switch != MID)
                { // if previous state is not mid change, this allows keyboard to toggle spin top mode
                    g_robot_state.spintop_mode = 1;
                }
            }
            else if (g_remote.controller.left_switch == UP) // launch on - off
            {
                if (g_key_prev.prev_left_switch != UP)
                { // if previous state is not mid change, this allows keyboard to toggle spin top mode
                    g_robot_state.spintop_mode = 0;
                }
                g_launch_target.flywheel_enabled = 1;
            }
            g_key_prev.prev_left_switch = g_remote.controller.left_switch;
            /* Chassis ends here */

            /* Gimbal starts here */
            if ((g_remote.controller.right_switch == UP) || (g_remote.mouse.right == 1)) // mouse right button auto aim
            {
                if (g_orin_data.receiving.auto_aiming.yaw != 0 || g_orin_data.receiving.auto_aiming.pitch != 0)
                {
                    g_robot_state.gimbal_yaw_angle = (1 - 0.2f) * g_robot_state.gimbal_yaw_angle + (0.2f) * (g_imu.rad.yaw - g_orin_data.receiving.auto_aiming.yaw / 180.0f * PI);         // + orin
                    g_robot_state.gimbal_pitch_angle = (1 - 0.2f) * g_robot_state.gimbal_pitch_angle + (0.2f) * (g_imu.rad.pitch - g_orin_data.receiving.auto_aiming.pitch / 180.0f * PI); // + orin
                }
            }
            else if (g_remote.controller.right_switch == MID)
            {
                g_robot_state.gimbal_yaw_angle -= (g_remote.controller.right_stick.x / 50000.0f + g_remote.mouse.x / 10000.0f);    // controller and mouse
                g_robot_state.gimbal_pitch_angle -= (g_remote.controller.right_stick.y / 100000.0f - g_remote.mouse.y / 50000.0f); // controller and mouse
            }
            /* Gimbal ends here */

            /* Launch control starts here */
            g_launch_target.heat_count++;
            g_launch_target.prev_burst_launch_flag = g_launch_target.burst_launch_flag;
            if (Referee_Robot_State.Shooter_Heat_1 < (Referee_Robot_State.Heat_Max-10))
            {
                if (g_remote.controller.wheel < -50.0f)
                { // dial wheel forward single fire
                    g_launch_target.single_launch_flag = 1;
                    g_launch_target.burst_launch_flag = 0;
                }
                else if ((g_remote.controller.wheel > 50.0f) || (g_remote.mouse.left == 1))
                { // dial wheel backward burst fire
                    g_launch_target.single_launch_flag = 0;
                    g_launch_target.burst_launch_flag = 1;
                    g_launch_target.launch_freq_count++;
                }
                else
                { // dial wheel mid stop fire
                    g_launch_target.single_launch_flag = 0;
                    g_launch_target.single_launch_finished_flag = 0;
                    g_launch_target.burst_launch_flag = 0;
                    g_launch_target.launch_freq_count = 0;
                    g_launch_target.feed_angle = DJI_Motor_Get_Total_Angle(g_motor_feed);
                }
            }
            else
            {
                g_launch_target.single_launch_flag = 0;
                g_launch_target.single_launch_finished_flag = 0;
                g_launch_target.burst_launch_flag = 0;
            }
            /* Launch control ends here */

            /* Keyboard Toggles Start Here */
            if (g_remote.keyboard.B == 1 && g_key_prev.prev_B == 0)
            {
                _toggle_robot_state(&g_launch_target.flywheel_enabled);
            }
            if (g_remote.keyboard.G == 1 && g_key_prev.prev_G == 0)
            {
                _toggle_robot_state(&g_robot_state.spintop_mode);
            }
            if (g_remote.keyboard.V == 1 && g_key_prev.prev_V == 0)
            {
                _toggle_robot_state(&g_robot_state.UI_enabled);
            }
            if (g_remote.keyboard.Z == 1 && g_key_prev.prev_Z == 0)
            {
                Referee_Robot_State.Manual_Level++;
                __MAX_LIMIT(Referee_Robot_State.Manual_Level,1,10);
            }
            if (g_remote.keyboard.Shift == 1 || (g_remote.controller.wheel > 50.0f && !g_launch_target.flywheel_enabled))
            {
                g_supercap.supercap_enabled_flag = 1;
            }
            else
            {
                g_supercap.supercap_enabled_flag = 0;
            }
            g_key_prev.prev_B = g_remote.keyboard.B;
            g_key_prev.prev_G = g_remote.keyboard.G;
            g_key_prev.prev_V = g_remote.keyboard.V;
            g_key_prev.prev_Z = g_remote.keyboard.Z;
            g_key_prev.prev_Shift = g_remote.keyboard.Shift;
            /* Keyboard Toggles Start Here */

            /* AutoAiming Flag, not used only for debug */
            g_launch_target.prev_reverse_flag = g_launch_target.reverse_flag;
            if (g_remote.mouse.right == 1 || (g_remote.controller.wheel < -50.0f && g_launch_target.flywheel_enabled)
               || (!g_launch_target.burst_launch_flag && g_launch_target.prev_burst_launch_flag))
            {
                g_launch_target.reverse_flag = 1;
                g_launch_target.calculated_heat = Referee_Robot_State.Shooter_Heat_1;
            }
            else
            {
                g_launch_target.reverse_flag = 0;
            }
            
            if(Referee_System.Robot_State.Chassis_Power_Output == 0)
            {
                g_robot_state.spintop_mode = 0;
            }

            /* Hardware Limits */
            g_robot_state.gimbal_yaw_angle = fmod(g_robot_state.gimbal_yaw_angle, 2 * PI);
            __MAX_LIMIT(g_robot_state.gimbal_pitch_angle, -0.4f, 0.4f);
            __MAX_LIMIT(g_robot_state.chassis_x_speed, -MAX_SPEED, MAX_SPEED);
            __MAX_LIMIT(g_robot_state.chassis_y_speed, -MAX_SPEED, MAX_SPEED);

            /* power buffer*/
            // float power_buffer = Referee_System.Power_n_Heat.Chassis_Power_Buffer / 60.0f;
            // if (power_buffer < 0.8f)
            // {
            //     g_robot_state.chassis_x_speed *= pow(power_buffer,1);
            //     g_robot_state.chassis_y_speed *= pow(power_buffer,1);
            //     g_robot_state.chassis_omega *= pow(power_buffer,1);
            // }
        }
    }
    else
    {
        if (g_remote.controller.right_switch == DOWN)
        {
            g_robot_state.safely_started = 1;
        }
    }
}

void _toggle_robot_state(uint8_t *state)
{
    *state ^= 0x01;
}