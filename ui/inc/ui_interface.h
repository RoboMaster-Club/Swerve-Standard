//
// Created by bismarckkk on 2024/2/17.
//

#ifndef SERIAL_TEST_UI_INTERFACE_H
#define SERIAL_TEST_UI_INTERFACE_H

#include <stdio.h>
#include "ui_types.h"
#include "bsp_crc.h"
#include "bsp_uart.h"
#include "bsp_serial.h"
#include "referee_system.h"

extern int ui_self_id;
extern UART_Instance_t *g_referee_uart_instance_ptr;

void print_message(const uint8_t* message, int length);

#define SEND_MESSAGE(message, length) UART_Transmit(g_referee_uart_instance_ptr,message,length,UART_DMA) //print_message(message, length)

void ui_proc_1_frame(ui_1_frame_t *msg);
void ui_proc_2_frame(ui_2_frame_t *msg);
void ui_proc_5_frame(ui_5_frame_t *msg);
void ui_proc_7_frame(ui_7_frame_t *msg);
void ui_proc_string_frame(ui_string_frame_t *msg);

#endif //SERIAL_TEST_UI_INTERFACE_H
