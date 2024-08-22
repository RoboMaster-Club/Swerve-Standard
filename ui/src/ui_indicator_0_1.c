//
// Created by RM UI Designer
//

#include "ui_indicator_0_1.h"
#include "string.h"

#define FRAME_ID 1
#define GROUP_ID 0
#define START_ID 1

ui_string_frame_t ui_indicator_0_1;

ui_interface_string_t* ui_indicator_0_Spintop_Text = &ui_indicator_0_1.option;

void _ui_init_indicator_0_1() {
    ui_indicator_0_1.option.figure_name[0] = FRAME_ID;
    ui_indicator_0_1.option.figure_name[1] = GROUP_ID;
    ui_indicator_0_1.option.figure_name[2] = START_ID;
    ui_indicator_0_1.option.operate_tpyel = 1;
    ui_indicator_0_1.option.figure_tpye = 7;
    ui_indicator_0_1.option.layer = 0;
    ui_indicator_0_1.option.font_size = 16;
    ui_indicator_0_1.option.start_x = 100;
    ui_indicator_0_1.option.start_y = 760;
    ui_indicator_0_1.option.color = 1;
    ui_indicator_0_1.option.str_length = 7;
    ui_indicator_0_1.option.width = 2;
    strcpy(ui_indicator_0_Spintop_Text->string, "SPINTOP");

    ui_proc_string_frame(&ui_indicator_0_1);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_1, sizeof(ui_indicator_0_1));
}

void _ui_update_indicator_0_1() {
    ui_indicator_0_1.option.operate_tpyel = 2;

    ui_proc_string_frame(&ui_indicator_0_1);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_1, sizeof(ui_indicator_0_1));
}

void _ui_remove_indicator_0_1() {
    ui_indicator_0_1.option.operate_tpyel = 3;

    ui_proc_string_frame(&ui_indicator_0_1);
    SEND_MESSAGE((uint8_t *) &ui_indicator_0_1, sizeof(ui_indicator_0_1));
}