//
// Created by RM UI Designer
//

#include "ui_indicator_0_8.h"
#include "string.h"

#define FRAME_ID 1
#define GROUP_ID 0
#define START_ID 8

ui_string_frame_t ui_indicator_0_8;

ui_interface_string_t* ui_indicator_0_Autoaim_Off = &ui_indicator_0_8.option;

void _ui_init_indicator_0_8() {
    ui_indicator_0_8.option.figure_name[0] = FRAME_ID;
    ui_indicator_0_8.option.figure_name[1] = GROUP_ID;
    ui_indicator_0_8.option.figure_name[2] = START_ID;
    ui_indicator_0_8.option.operate_tpyel = 1;
    ui_indicator_0_8.option.figure_tpye = 7;
    ui_indicator_0_8.option.layer = 0;
    ui_indicator_0_8.option.font_size = 16;
    ui_indicator_0_8.option.start_x = 340;
    ui_indicator_0_8.option.start_y = 720;
    ui_indicator_0_8.option.color = 1;
    ui_indicator_0_8.option.str_length = 3;
    ui_indicator_0_8.option.width = 2;
    strcpy(ui_indicator_0_Autoaim_Off->string, "OFF");

    ui_proc_string_frame(&ui_indicator_0_8);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_8, sizeof(ui_indicator_0_8));
}

void _ui_update_indicator_0_8() {
    ui_indicator_0_8.option.operate_tpyel = 2;

    ui_proc_string_frame(&ui_indicator_0_8);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_8, sizeof(ui_indicator_0_8));
}

void _ui_remove_indicator_0_8() {
    ui_indicator_0_8.option.operate_tpyel = 3;

    ui_proc_string_frame(&ui_indicator_0_8);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_8, sizeof(ui_indicator_0_8));
}