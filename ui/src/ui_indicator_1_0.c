//
// Created by RM UI Designer
//

#include "ui_indicator_1_0.h"

#define FRAME_ID 1
#define GROUP_ID 1
#define START_ID 0
#define OBJ_NUM 7
#define FRAME_OBJ_NUM 7

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_indicator_1_0;
ui_interface_rect_t *ui_indicator_1_Flywheel_Select = (ui_interface_rect_t *)&(ui_indicator_1_0.data[0]);
ui_interface_rect_t *ui_indicator_1_Spintop_Select = (ui_interface_rect_t *)&(ui_indicator_1_0.data[1]);
ui_interface_rect_t *ui_indicator_1_Autoaim_Select = (ui_interface_rect_t *)&(ui_indicator_1_0.data[2]);
ui_interface_number_t *ui_indicator_1_Supercap = (ui_interface_number_t *)&(ui_indicator_1_0.data[3]);
ui_interface_line_t *ui_indicator_1_Aim_V_Line = (ui_interface_line_t *)&(ui_indicator_1_0.data[4]);
ui_interface_line_t *ui_indicator_1_Aim_H_Line = (ui_interface_line_t *)&(ui_indicator_1_0.data[5]);
ui_interface_number_t *ui_indicator_1_Level_Indicator = (ui_interface_number_t *)&(ui_indicator_1_0.data[6]);

void _ui_init_indicator_1_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_indicator_1_0.data[i].figure_name[0] = FRAME_ID;
        ui_indicator_1_0.data[i].figure_name[1] = GROUP_ID;
        ui_indicator_1_0.data[i].figure_name[2] = i + START_ID;
        ui_indicator_1_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_indicator_1_0.data[i].operate_tpyel = 0;
    }

    ui_indicator_1_Flywheel_Select->figure_tpye = 1;
    ui_indicator_1_Flywheel_Select->layer = 1;
    ui_indicator_1_Flywheel_Select->start_x = 270;
    ui_indicator_1_Flywheel_Select->start_y = 780;
    ui_indicator_1_Flywheel_Select->color = 6;
    ui_indicator_1_Flywheel_Select->width = 4;
    ui_indicator_1_Flywheel_Select->end_x = 320;
    ui_indicator_1_Flywheel_Select->end_y = 810;

    ui_indicator_1_Spintop_Select->figure_tpye = 1;
    ui_indicator_1_Spintop_Select->layer = 1;
    ui_indicator_1_Spintop_Select->start_x = 335;
    ui_indicator_1_Spintop_Select->start_y = 740;
    ui_indicator_1_Spintop_Select->color = 6;
    ui_indicator_1_Spintop_Select->width = 4;
    ui_indicator_1_Spintop_Select->end_x = 385;
    ui_indicator_1_Spintop_Select->end_y = 770;

    ui_indicator_1_Autoaim_Select->figure_tpye = 1;
    ui_indicator_1_Autoaim_Select->layer = 1;
    ui_indicator_1_Autoaim_Select->start_x = 270;
    ui_indicator_1_Autoaim_Select->start_y = 700;
    ui_indicator_1_Autoaim_Select->color = 6;
    ui_indicator_1_Autoaim_Select->width = 4;
    ui_indicator_1_Autoaim_Select->end_x = 320;
    ui_indicator_1_Autoaim_Select->end_y = 730;

    ui_indicator_1_Supercap->figure_tpye = 6;
    ui_indicator_1_Supercap->layer = 1;
    ui_indicator_1_Supercap->font_size = 30;
    ui_indicator_1_Supercap->start_x = 920;
    ui_indicator_1_Supercap->start_y = 300;
    ui_indicator_1_Supercap->color = 6;
    ui_indicator_1_Supercap->number = 86;
    ui_indicator_1_Supercap->width = 3;

    ui_indicator_1_Aim_V_Line->figure_tpye = 0;
    ui_indicator_1_Aim_V_Line->layer = 0;
    ui_indicator_1_Aim_V_Line->start_x = 925;
    ui_indicator_1_Aim_V_Line->start_y = 455;
    ui_indicator_1_Aim_V_Line->end_x = 925;
    ui_indicator_1_Aim_V_Line->end_y = 485;
    ui_indicator_1_Aim_V_Line->color = 3;
    ui_indicator_1_Aim_V_Line->width = 2;

    ui_indicator_1_Aim_H_Line->figure_tpye = 0;
    ui_indicator_1_Aim_H_Line->layer = 0;
    ui_indicator_1_Aim_H_Line->start_x = 910;
    ui_indicator_1_Aim_H_Line->start_y = 470;
    ui_indicator_1_Aim_H_Line->end_x = 940;
    ui_indicator_1_Aim_H_Line->end_y = 470;
    ui_indicator_1_Aim_H_Line->color = 3;
    ui_indicator_1_Aim_H_Line->width = 2;
    
    ui_indicator_1_Level_Indicator->figure_tpye = 6;
    ui_indicator_1_Level_Indicator->layer = 1;
    ui_indicator_1_Level_Indicator->font_size = 20;
    ui_indicator_1_Level_Indicator->start_x = 1020;
    ui_indicator_1_Level_Indicator->start_y = 100;
    ui_indicator_1_Level_Indicator->color = 1;
    ui_indicator_1_Level_Indicator->number = 1;
    ui_indicator_1_Level_Indicator->width = 2;

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_indicator_1_0);
    SEND_MESSAGE((uint8_t *) &ui_indicator_1_0, sizeof(ui_indicator_1_0));
}

void _ui_update_indicator_1_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_indicator_1_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_indicator_1_0);
    SEND_MESSAGE((uint8_t *) &ui_indicator_1_0, sizeof(ui_indicator_1_0));
}

void _ui_remove_indicator_1_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_indicator_1_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_indicator_1_0);
    SEND_MESSAGE((uint8_t *) &ui_indicator_1_0, sizeof(ui_indicator_1_0));
}
