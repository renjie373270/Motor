//
// Created by Steven on 2019/8/14.
//

#include "encoder.h"

#define EncoderK0()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)
#define EncoderA0()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_5)
#define EncoderB0()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_4)

#define EncoderK1()   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14)
#define EncoderA1()   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13)
#define EncoderB1()   GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_12)


/**
 * 初始化编码器IO口
 * 顺时针先触发B，逆时针先触发A，按下时K有效
 * */
void initEncoderGPIO() {
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;

    //K0 - PA6, A0 - PA5, B0 - PA4
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    //K1 - PB14, A1 - PB13, B1 - PB12
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
 * 初始化编码器中断向量
 * */
void initEncoderNVIC() {
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 3;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}

/**
 * 编码器外部中断配置
 * */
void initEncoderEXTI() {
    EXTI_InitTypeDef EXTI_InitStruct;

    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;

    //编码器0
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4 | EXTI_PinSource5 | EXTI_PinSource6);
    EXTI_InitStruct.EXTI_Line = EXTI_Line4 | EXTI_Line5 | EXTI_Line6;
    EXTI_Init(&EXTI_InitStruct);

    //编码器1
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12 | EXTI_PinSource13 | EXTI_PinSource14);
    EXTI_InitStruct.EXTI_Line = EXTI_Line12 | EXTI_Line13 | EXTI_Line14;
    EXTI_Init(&EXTI_InitStruct);
}

/**
 * 编码器0检测
 * */
void readEncoder0Status() {

    if(EXTI_GetITStatus(EXTI_Line6) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line6);
        if(!EncoderK0()) {
            confirmArray[0] = TRUE;
        }
    }
    if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line5);
        if(!EncoderA0() && EncoderB0()) {
            positionArray[0] --;
        }
    }
    if(EXTI_GetITStatus(EXTI_Line4) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line4);
        if(EncoderA0() && !EncoderB0()) {
            positionArray[0] ++;
        }
    }
}

/**
 * 编码器1检测
 * */
void readEncoder1Status() {
    if(EXTI_GetITStatus(EXTI_Line14) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line14);
        if(!EncoderK1()) {
            confirmArray[1] = TRUE;
        }
    }
    if(EXTI_GetITStatus(EXTI_Line13) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line13);
        if(!EncoderA1() && EncoderB1()) {
            positionArray[1] --;
        }
        while (!EncoderA1() && EncoderB1());
    }
    if(EXTI_GetITStatus(EXTI_Line12) != RESET) {
        EXTI_ClearITPendingBit(EXTI_Line12);
        if(EncoderA1() && !EncoderB1()) {
            positionArray[1] ++;
        }
        while (EncoderA1() && !EncoderB1());
    }
}

/**
 * 检测编码器转动方向和角度
 * */
void readEncoderStatus() {
    readEncoder1Status();
    readEncoder0Status();
}

/**
 * 初始化编码器相关配置
 * */
void initEncoder() {
    initEncoderGPIO();
    initEncoderNVIC();
    initEncoderEXTI();
}
