//
// Created by Steven on 2019/8/14.
//

#ifndef MOTOR_ENCODER_H
#define MOTOR_ENCODER_H

#include "main.h"

#define EncoderKey() GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)
#define EncoderA()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define EncoderB()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)

void initEncoder(void);

#endif //MOTOR_ENCODER_H
