//
// Created by Steven on 2019/8/14.
//

#include "motor.h"
#include "math.h"


//当前位置
int position1 = 0;
uint8_t position1Confirm = FALSE;

//A1代表A+, A2代表A-
#define A1_TO_A2()  GPIO_SetBits(GPIOA, GPIO_Pin_0); GPIO_ResetBits(GPIOA, GPIO_Pin_1); delayInMilliSeconds(5)
#define A2_TO_A1()  GPIO_SetBits(GPIOA, GPIO_Pin_1); GPIO_ResetBits(GPIOA, GPIO_Pin_0); delayInMilliSeconds(5)
#define A_Off()   GPIO_SetBits(GPIOA, GPIO_Pin_0); GPIO_SetBits(GPIOA, GPIO_Pin_1);     delayInMilliSeconds(5)

#define B1_TO_B2()  GPIO_SetBits(GPIOA, GPIO_Pin_2); GPIO_ResetBits(GPIOA, GPIO_Pin_3); delayInMilliSeconds(5)
#define B2_TO_B1()  GPIO_SetBits(GPIOA, GPIO_Pin_3); GPIO_ResetBits(GPIOA, GPIO_Pin_2); delayInMilliSeconds(5)
#define B_Off()   GPIO_SetBits(GPIOA, GPIO_Pin_2); GPIO_SetBits(GPIOA, GPIO_Pin_3);     delayInMilliSeconds(5)


/**
 * 初始化步进电机相关IO口
 * */
void initMotorGPIO() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);

    gpio.GPIO_Pin  = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType= GPIO_OType_PP;
    gpio.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOA , &gpio);
}

/**
 * 顺时针转动
 * */
void forward() {
    B1_TO_B2();//45
    A_Off();//90
    A2_TO_A1();//135
    B_Off();//180
    B2_TO_B1();//225
    A_Off();//270
    A1_TO_A2();//315
    B_Off();//360
}

/**
 * 逆时针转动
 * */
void reverse() {
    B2_TO_B1();//315
    A_Off();//270
    A2_TO_A1();//225
    B_Off();//180
    B1_TO_B2();//135
    A_Off();//90
    A1_TO_A2();//45
    B_Off();//0
}

/**
 * 正向转动，输入参数为角度
 * 步距角18度，减速比1:275
 * */
void forwardMotor(float degrees) {
    float stepAngle = 18 / 275.0;
    uint32_t remainSteps = degrees / stepAngle;
    uint32_t circles = remainSteps / 4;
    while (circles--) {
        forward();
    }
    A_Off();
    B_Off();
}

/**
 * 反向转动
 * */
void reverseMotor(float degrees) {
    float stepAngle = 18 / 275.0;
    uint32_t remainSteps = degrees / stepAngle;
    uint32_t circles = remainSteps / 4;
    while (circles--) {
        reverse();
    }
    A_Off();
    B_Off();
}

/**
 * 电机状态更新
 * */
 void updateMotorPosition() {
    if(position1Confirm == TRUE) {
        if(position1 > 0) {
            forwardMotor(position1 * 1.0);
        }
        if(position1 < 0) {
            reverseMotor(-position1 * 1.0);
        }
        position1Confirm = FALSE;
        position1 = 0;
    }
 }
 