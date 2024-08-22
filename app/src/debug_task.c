#include "debug_task.h"
#include "bsp_serial.h"
#include "launch_task.h"
#include "remote.h"
#include "gimbal_task.h"
#include "Swerve_Locomotion.h"
#include "user_math.h"
#include "imu_task.h"
#include "robot.h"
#include "referee_system.h"
#include "jetson_orin.h"
#include "bsp_daemon.h"
#include "launch_task.h"

extern Robot_State_t g_robot_state;
extern DJI_Motor_Handle_t *g_yaw;
extern IMU_t g_imu;
extern Swerve_Module_t g_swerve_rl, g_swerve_fr;
extern Remote_t g_remote; 
extern Launch_Target_t g_launch_target;
extern Daemon_Instance_t *g_daemon_instances[3];
extern Daemon_Instance_t *g_remote_daemon;
extern Daemon_Instance_t *g_referee_daemon_instance_ptr;
extern float test_tmd;
//#define PRINT_RUNTIME_STATS
#ifdef PRINT_RUNTIME_STATS
char g_debug_buffer[1024*2] = {0};
#endif

const char* top_border = "\r\n\r\n\r\n/***** System Info *****/\r\n";
const char* bottom_border = "/***** End of Info *****/\r\n";

#define DEBUG_ENABLED

void Debug_Task_Loop(void)
{
#ifdef DEBUG_ENABLED
    //static uint32_t counter = 0;
    #ifdef PRINT_RUNTIME_STATS
    if (counter % 100 == 0) // Print every 100 cycles
    {
        vTaskGetRunTimeStats(g_debug_buffer);
        DEBUG_PRINTF(&huart6, "%s", top_border);
        DEBUG_PRINTF(&huart6, "%s", g_debug_buffer);
        DEBUG_PRINTF(&huart6, "%s", bottom_border);
    }
    #endif
    //DEBUG_PRINTF(&huart6, ">time:%.1f\n>ref:%f\n",(float) counter / 1000.0f * DEBUG_PERIOD,Referee_Robot_State.Chassis_Power);
    // DEBUG_PRINTF(&huart6, ">time:%.1f\n>yaw:%f\n>pitch:%f\n>roll:%f\n", (float) counter / 1000.0f * DEBUG_PERIOD, 
    //             g_imu.deg.yaw, g_imu.deg.pitch, g_imu.deg.roll);
    // DEBUG_PRINTF(&huart6, ">remote_daemon:%d\n", g_remote_daemon->counter);
    // counter++;
    // if (counter > 0xFFFFFFFF) {
    //     counter = 0;
    // }

    DEBUG_PRINTF(&huart6, ">target_angle:%f\n>actual_angle:%f\n",
    g_swerve_fr.azimuth_motor->angle_pid->ref,g_swerve_fr.azimuth_motor->stats->absolute_angle_rad);
#endif
}