//
// Created by RM UI Designer
//

#include "ui_indicator_0_9.h"
#include "string.h"

#define FRAME_ID 1
#define GROUP_ID 0
#define START_ID 9

ui_string_frame_t ui_indicator_0_9;

ui_interface_string_t* ui_indicator_0_Supercap_Percent = &ui_indicator_0_9.option;

void _ui_init_indicator_0_9() {
    ui_indicator_0_9.option.figure_name[0] = FRAME_ID;
    ui_indicator_0_9.option.figure_name[1] = GROUP_ID;
    ui_indicator_0_9.option.figure_name[2] = START_ID;
    ui_indicator_0_9.option.operate_tpyel = 1;
    ui_indicator_0_9.option.figure_tpye = 7;
    ui_indicator_0_9.option.layer = 0;
    ui_indicator_0_9.option.font_size = 30;
    ui_indicator_0_9.option.start_x = 980;
    ui_indicator_0_9.option.start_y = 300;
    ui_indicator_0_9.option.color = 6;
    ui_indicator_0_9.option.str_length = 1;
    ui_indicator_0_9.option.width = 3;
    strcpy(ui_indicator_0_Supercap_Percent->string, "%");

    ui_proc_string_frame(&ui_indicator_0_9);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_9, sizeof(ui_indicator_0_9));
}

void _ui_update_indicator_0_9() {
    ui_indicator_0_9.option.operate_tpyel = 2;

    ui_proc_string_frame(&ui_indicator_0_9);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_9, sizeof(ui_indicator_0_9));
}

void _ui_remove_indicator_0_9() {
    ui_indicator_0_9.option.operate_tpyel = 3;

    ui_proc_string_frame(&ui_indicator_0_9);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_9, sizeof(ui_indicator_0_9));
}