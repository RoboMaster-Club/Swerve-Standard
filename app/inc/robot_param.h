#ifndef ROBOT_PARAM_H
#define ROBOT_PARAM_H

#define DEBUG

/* Motor ID */
#define LEFT_FRONT_ID 0x00
#define RIGHT_FRONT_ID 0x01
#define RIGHT_REAR_ID 0x02
#define LEFT_REAR_ID 0x03
#define LEFT_TOE_ID 0x06
#define RIGHT_TOE_ID 0x05

/* Motor */
#define LEFT_FRONT_OFFSET -.64f
#define LEFT_REAR_OFFSET -2.11f
#define RIGHT_FRONT_OFFSET -3.70f
#define RIGHT_REAR_OFFSET 0.45f

#define MAX_FORWARD_VEL 5.0f
#define MAX_YAW_VEL PI

/* Robot Stats*/
#define HALF_THIGH_DISTANCE 0.035f
#define THIGH_LENGTH 0.14f
#define CALF_LENGTH 0.24f
#define TOE_WHEEL_RADIUS 0.06f // meter

/* Limit */
#define THIGH_ANG_RANGE 45.0f //degree

/* Control */
#define INIT_CHASSIS_HEIGHT 0.16//0.144f
#define INIT_CHASSIS_ANGLE 90.0f

#endif
