//
// Created by Steven on 2019/8/14.
//

#ifndef MOTOR_MOTOR_H
#define MOTOR_MOTOR_H

#include "main.h"

#define  MOTOR_SH_PORT GPIOA
#define  MOTOR_SH_PIN  GPIO_Pin_3
#define  MOTOR_SH_RCC RCC_AHBPeriph_GPIOA

#define  MOTOR_DS_PORT GPIOA
#define  MOTOR_DS_PIN  GPIO_Pin_1
#define  MOTOR_DS_RCC RCC_AHBPeriph_GPIOA

#define  MOTOR_ST_PORT GPIOA
#define  MOTOR_ST_PIN  GPIO_Pin_2
#define  MOTOR_ST_RCC RCC_AHBPeriph_GPIOA

extern int8_t  positionArray[5];
extern uint8_t confirmArray[5];

void initMotorGPIO(void);
void updateMotorPosition(void);
#endif //MOTOR_MOTOR_H
