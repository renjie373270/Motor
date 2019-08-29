//
// Created by Steven on 2019/8/27.
//

#ifndef MOTOR_DISPLAY_H
#define MOTOR_DISPLAY_H

#include "main.h"

#define  SEG_DS_PORT GPIOA
#define  SEG_DS_PIN  GPIO_Pin_10
#define  SEG_DS_RCC RCC_AHBPeriph_GPIOA

#define  SEG_ST_PORT GPIOA
#define  SEG_ST_PIN  GPIO_Pin_11
#define  SEG_ST_RCC RCC_AHBPeriph_GPIOA

#define  SEG_SH_PORT GPIOA
#define  SEG_SH_PIN  GPIO_Pin_12
#define  SEG_SH_RCC RCC_AHBPeriph_GPIOA

void initDisplayDevice(void);
void display(uint8_t num1, uint8_t num2);

#endif //MOTOR_DISPLAY_H
