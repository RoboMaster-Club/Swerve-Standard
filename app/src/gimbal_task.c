#include "gimbal_task.h"
#include "dji_motor.h"
#include "robot.h"
#include "remote.h"
#include "imu_task.h"
#include "user_math.h"
#include "jetson_orin.h"
#include <math.h>
extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
extern IMU_t g_imu;
float gimbal_test = 0;
uint64_t t = 0;
DJI_Motor_Handle_t *g_yaw, *g_pitch;
Gimbal_Target_t g_gimbal_target;
PID_t autoaim_yaw_angle_pid = {
    .kp = 20.0f,
    .kd = 300.0f,
    .output_limit = 25,
};
PID_t autoaim_yaw_velocity_pid = {
    .kp = 1000.0f,
    .ki = 0.0f,
    .kf = 2000.0f,
    .feedforward_limit = 5000.0f,
    .integral_limit = 5000.0f,
    .output_limit = GM6020_MAX_CURRENT,
};
PID_t autoaim_pitch_angle_pid = {
    .kp = 25.0f,
    .kd = 400.0f,
    .output_limit = 50.0f,
};
PID_t autoaim_pitch_velocity_pid = {
    .kp = 4500.0f,
    .ki = 0.8f,
    .integral_limit = 4000.0f,
    .output_limit = GM6020_MAX_CURRENT,
};
void Gimbal_Task_Init()
{
    Motor_Config_t yaw_motor_config = {
        .can_bus = 1,
        .speed_controller_id = 3,
        .offset = 2400,
        .control_mode = POSITION_VELOCITY_SERIES,
        .motor_reversal = MOTOR_REVERSAL_NORMAL,
        .use_external_feedback = 1,
        .external_feedback_dir = 1,
        .external_angle_feedback_ptr = &g_imu.rad.yaw,
        .external_velocity_feedback_ptr = &(g_imu.bmi088_raw.gyro[2]),
        .angle_pid =
            {
                .kp = 25.0f,
                .kd = 100.0f,
                .output_limit = 25,
            },
        .velocity_pid =
            {
                .kp = 5000.0f,
                .ki = 0.0f,
                .kf = 1000.0f,
                .feedforward_limit = 5000.0f,
                .integral_limit = 5000.0f,
                .output_limit = GM6020_MAX_CURRENT,
            },
    };

    Motor_Config_t pitch_motor_config = {
        .can_bus = 1,
        .speed_controller_id = 2,
        .offset = 4460,
        .use_external_feedback = 1,
        .external_feedback_dir = -1,
        .external_angle_feedback_ptr = &g_imu.rad.roll, // pitch
        .external_velocity_feedback_ptr = &(g_imu.bmi088_raw.gyro[0]),
        .control_mode = POSITION_VELOCITY_SERIES,
        .motor_reversal = MOTOR_REVERSAL_NORMAL,
        .angle_pid =
            {
                .kp = 25.0f,
                .kd = 100.0f,
                .output_limit = 50.0f,
            },
        .velocity_pid =
            {
                .kp = 4500.0f,
                .ki = 0.8f,
                .integral_limit = 4000.0f,
                .output_limit = GM6020_MAX_CURRENT,
            },
    };

    g_yaw = DJI_Motor_Init(&yaw_motor_config, GM6020);
    g_pitch = DJI_Motor_Init(&pitch_motor_config, GM6020);
}

void Gimbal_Ctrl_Loop()
{
    if (g_robot_state.enabled)
    {
        // if (g_robot_state.autoaiming_enabled) {
        //     DJI_Motor_Set_Control_Mode(g_yaw, TORQUE_CONTROL);
        //     // DJI_Motor_Set_Control_Mode(g_pitch, TORQUE_CONTROL);
        //     float target_yaw_vel = PID(&autoaim_yaw_angle_pid, -g_orin_data.receiving.auto_aiming.yaw / 180.0f * PI);
        //     g_yaw->output_current = PID(&autoaim_yaw_velocity_pid, target_yaw_vel - g_yaw->external_feedback_dir * (*g_yaw->external_velocity_feedback_ptr));
        //     // DJI_Motor_Set_Control_Mode(g_pitch, POSITION_VELOCITY_SERIES);
        //     // DJI_Motor_Set_Angle(g_pitch, g_robot_state.gimbal_pitch_angle);
        //     float target_pitch_vel = PID(&autoaim_pitch_angle_pid, g_orin_data.receiving.auto_aiming.pitch / 180.0f * PI);
        //     g_pitch->output_current = PID(&autoaim_pitch_velocity_pid, target_pitch_vel - g_pitch->external_feedback_dir * (*g_pitch->external_velocity_feedback_ptr));
        // }
        // else{
        //     DJI_Motor_Set_Control_Mode(g_yaw, POSITION_VELOCITY_SERIES);
        //     DJI_Motor_Set_Control_Mode(g_pitch, POSITION_VELOCITY_SERIES);
        //     DJI_Motor_Set_Angle(g_pitch, g_robot_state.gimbal_pitch_angle);
        //     DJI_Motor_Set_Angle(g_yaw, g_robot_state.gimbal_yaw_angle);
        // }
        if (g_robot_state.autoaiming_enabled) {
            g_yaw->angle_pid->kp = 11.0f;
            g_yaw->angle_pid->kd = 320.0f;
            g_yaw->velocity_pid->kf = 2000.0f;

            g_pitch->angle_pid->kp = 10.0f;
            g_pitch->angle_pid->kd = 400.0f;
            g_pitch->velocity_pid->kp = 4500.0f;
            g_pitch->velocity_pid->ki = 0.8f;
            DJI_Motor_Set_Angle(g_pitch, g_robot_state.gimbal_pitch_angle);
            DJI_Motor_Set_Angle(g_yaw, g_robot_state.gimbal_yaw_angle);
        } else {
            g_yaw->angle_pid->kp = 20.0f;
            g_yaw->angle_pid->kd = 150.0f;
            g_yaw->velocity_pid->kf = 1000.0f;

            g_pitch->angle_pid->kp = 25.0f;
            g_pitch->angle_pid->kd = 400.0f;
            g_pitch->velocity_pid->kp = 4500.0f;
            g_pitch->velocity_pid->ki = 0.8f;
            DJI_Motor_Set_Angle(g_pitch, g_robot_state.gimbal_pitch_angle);
            DJI_Motor_Set_Angle(g_yaw, g_robot_state.gimbal_yaw_angle);
        }
        
    }
    else
    {
        DJI_Motor_Disable(g_yaw);
        DJI_Motor_Disable(g_pitch);
    }
}
