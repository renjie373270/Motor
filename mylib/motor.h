//
// Created by Steven on 2019/8/14.
//

#ifndef MOTOR_MOTOR_H
#define MOTOR_MOTOR_H

#include "main.h"

extern int position1;
extern uint8_t position1Confirm;

void initMotorGPIO(void);
void forwardMotor(float degrees);
void reverseMotor(float degrees);
void updateMotorPosition(void);
#endif //MOTOR_MOTOR_H
