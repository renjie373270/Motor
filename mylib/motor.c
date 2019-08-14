//
// Created by Steven on 2019/8/14.
//

#include "motor.h"


//ת�ӵ�ǰλ��
#define STEP_1 1
#define STEP_2 2
#define STEP_3 3
#define STEP_4 4

//A1����A+, A2����A-
#define A1_TO_A2()  GPIO_SetBits(GPIOA, GPIO_Pin_0); GPIO_ResetBits(GPIOA, GPIO_Pin_1); delayInMilliSeconds(5)
#define A2_TO_A1()  GPIO_SetBits(GPIOA, GPIO_Pin_1); GPIO_ResetBits(GPIOA, GPIO_Pin_0); delayInMilliSeconds(5)
#define A_Off()   GPIO_SetBits(GPIOA, GPIO_Pin_0); GPIO_SetBits(GPIOA, GPIO_Pin_1);     delayInMilliSeconds(5)

#define B1_TO_B2()  GPIO_SetBits(GPIOA, GPIO_Pin_2); GPIO_ResetBits(GPIOA, GPIO_Pin_3); delayInMilliSeconds(5)
#define B2_TO_B1()  GPIO_SetBits(GPIOA, GPIO_Pin_3); GPIO_ResetBits(GPIOA, GPIO_Pin_2); delayInMilliSeconds(5)
#define B_Off()   GPIO_SetBits(GPIOA, GPIO_Pin_2); GPIO_SetBits(GPIOA, GPIO_Pin_3);     delayInMilliSeconds(5)

uint8_t currentStep = STEP_4;

/**
 * ��ʼ������������IO��
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
 * ˳ʱ��ת��
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
 * ��ʱ��ת��
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
 * ����ת�����������Ϊ�Ƕ�
 * �����18�ȣ����ٱ�1:275
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
 * ����ת��
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

