//
// Created by RM UI Designer
//

#ifndef UI_H
#define UI_H
#ifdef __cplusplus
extern "C" {
#endif

#include "ui_interface.h"

#include "ui_indicator_0_0.h"
#include "ui_indicator_0_1.h"
#include "ui_indicator_0_2.h"
#include "ui_indicator_0_3.h"
#include "ui_indicator_0_4.h"
#include "ui_indicator_0_5.h"
#include "ui_indicator_0_6.h"
#include "ui_indicator_0_7.h"
#include "ui_indicator_0_8.h"
#include "ui_indicator_0_9.h"
#include "ui_indicator_0_10.h"
#include "ui_indicator_0_11.h"

#define SEND_INTERVAL_MS (40)

#define ui_init_indicator_0()   \
_ui_init_indicator_0_0();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_1();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_2();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_3();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_4();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_5();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_6();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_7();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_8();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_9();       \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_10();      \
osDelay(SEND_INTERVAL_MS);      \
_ui_init_indicator_0_11();      \
osDelay(SEND_INTERVAL_MS)

#define ui_update_indicator_0() \
_ui_update_indicator_0_0();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_1();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_2();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_3();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_4();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_5();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_6();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_7();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_8();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_9();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_10();    \
osDelay(SEND_INTERVAL_MS);      \
_ui_update_indicator_0_11();    \
osDelay(SEND_INTERVAL_MS)

#define ui_remove_indicator_0() \
_ui_remove_indicator_0_0();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_1();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_2();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_3();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_4();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_5();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_6();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_7();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_8();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_9();     \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_10();    \
osDelay(SEND_INTERVAL_MS);      \
_ui_remove_indicator_0_11();    \
osDelay(SEND_INTERVAL_MS)               
    
#include "ui_indicator_1_0.h"

#define ui_init_indicator_1()   \
_ui_init_indicator_1_0();       \
osDelay(SEND_INTERVAL_MS)               

#define ui_update_indicator_1() \
_ui_update_indicator_1_0();     \
osDelay(SEND_INTERVAL_MS)               

#define ui_remove_indicator_1() \
_ui_remove_indicator_1_0();     \
osDelay(SEND_INTERVAL_MS)               

#ifdef __cplusplus
}
#endif

#endif //UI_H
