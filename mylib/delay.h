//
// Created by Steven on 2019/8/14.
//

#ifndef MOTOR_DELAY_H
#define MOTOR_DELAY_H

#include "main.h"

extern uint32_t sysTickCountDown;

void delayInit(void);
void delayInMilliSeconds(uint32_t x);

#endif //MOTOR_DELAY_H
