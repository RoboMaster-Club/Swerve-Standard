//
// Created by RM UI Designer
//

#ifndef UI_indicator_1_0_H
#define UI_indicator_1_0_H

#include "ui_interface.h"

extern ui_interface_rect_t *ui_indicator_1_Flywheel_Select;
extern ui_interface_rect_t *ui_indicator_1_Spintop_Select;
extern ui_interface_rect_t *ui_indicator_1_Autoaim_Select;
extern ui_interface_number_t *ui_indicator_1_Supercap;
extern ui_interface_line_t *ui_indicator_1_Aim_V_Line;
extern ui_interface_line_t *ui_indicator_1_Aim_H_Line;
extern ui_interface_number_t *ui_indicator_1_Level_Indicator;

void _ui_init_indicator_1_0();
void _ui_update_indicator_1_0();
void _ui_remove_indicator_1_0();

#endif //UI_indicator_1_0_H
