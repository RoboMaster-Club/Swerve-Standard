#include "chassis_task.h"

#include "dji_motor.h"
#include "robot.h"
#include "remote.h"
#include "imu_task.h"
#include "Swerve_Locomotion.h"

#define SPINTOP_RAMP_COEF (0.05f)
#define TRANSLATION_RAMP_COEF (0.05f)
#define SPIN_TOP_OMEGA (1.0f)

extern Robot_State_t g_robot_state;
extern Remote_t g_remote;
extern IMU_t g_imu;

float chassis_rad;

void Chassis_Task_Init()
{
    Swerve_Init();
    chassis_rad = TRACK_WIDTH * 0.5f * sqrtf(2.0f);
}

void Chassis_Ctrl_Loop()
{
    if (g_robot_state.enabled)
    {
        /*
         * scale spintop omega by inverse of translation speed to prioritize translation
         * spin_coeff = rw/(v + rw) // r = rad, w = desired omega (spin top omega), v = translational speed
         * chassis_omega *= spin_coeff
         */
        if (g_robot_state.spintop_mode)
        {
            float translation_speed = sqrtf(powf(g_robot_state.chassis_x_speed, 2) + powf(g_robot_state.chassis_y_speed, 2));
            float spin_coeff = chassis_rad * SPIN_TOP_OMEGA / (translation_speed + chassis_rad * SPIN_TOP_OMEGA);

            // ramp up to target omega
            float target_omega = SPIN_TOP_OMEGA * spin_coeff;
            g_robot_state.chassis_omega += SPINTOP_RAMP_COEF * (target_omega - g_robot_state.chassis_omega);
        }
        else
        {
            g_robot_state.chassis_omega *= (1 - SPINTOP_RAMP_COEF);
        }
        //g_robot_state.chassis_omega = (1-SPINTOP_RAMP_COEF)*g_robot_state.chassis_omega + SPINTOP_RAMP_COEF*g_robot_state.chassis_omega;
        g_robot_state.chassis_x_speed = (1 - TRANSLATION_RAMP_COEF)*g_robot_state.chassis_x_speed + TRANSLATION_RAMP_COEF*g_robot_state.chassis_x_speed;
        g_robot_state.chassis_y_speed = (1 - TRANSLATION_RAMP_COEF)*g_robot_state.chassis_y_speed + TRANSLATION_RAMP_COEF*g_robot_state.chassis_y_speed;

        Swerve_Drive(g_robot_state.chassis_x_speed, g_robot_state.chassis_y_speed, g_robot_state.chassis_omega);
    }
    else
    {
        Swerve_Disable();
    }
}