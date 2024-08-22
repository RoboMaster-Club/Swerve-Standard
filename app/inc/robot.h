#ifndef ROBOT_H
#define ROBOT_H

#include <stdint.h>
#include "user_math.h"

typedef struct
{
  uint8_t enabled;
  uint8_t safely_started;
  uint8_t spintop_mode;
  uint8_t autoaiming_enabled;
  uint8_t UI_enabled;
  float chassis_x_speed;
  float chassis_y_speed;
  float chassis_omega;

  float chassis_power_buffer[BUFFER_SIZE];
  uint16_t chassis_power_index;
  uint16_t chassis_power_count;
  float chassis_avg_power;
  float chassis_total_power;
  float power_increment_ratio;

  float gimbal_pitch_angle;
  float gimbal_yaw_angle;
  float vx;
  float vy;
  float vx_keyboard;
  float vy_keyboard;
} Robot_State_t;

typedef struct
{
  uint8_t prev_B;
  uint8_t prev_G;
  uint8_t prev_V;
  uint8_t prev_Z;
  uint8_t prev_Shift;
  uint8_t prev_left_switch;
} Key_Prev_t;

void Robot_Init(void);
void Robot_Ctrl_Loop(void);

extern Robot_State_t g_robot_state;

#endif // ROBOT_H
