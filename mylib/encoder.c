//
// Created by Steven on 2019/8/14.
//

#include "encoder.h"

/**
 * ��ʼ��������IO��
 * ˳ʱ���ȴ���B����ʱ���ȴ���A������ʱK��Ч
 * */
void initEncoderGPIO() {
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    //K - PA4, A - PA5, B - PA6
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/**
 * ��ʼ���������ж�����
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
 * �������ⲿ�ж�����
 * */
void initEncoderEXTI() {
    EXTI_InitTypeDef EXTI_InitStruct;

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource4 | EXTI_PinSource5 | EXTI_PinSource6);
    EXTI_InitStruct.EXTI_Line = EXTI_Line4 | EXTI_Line5 | EXTI_Line6;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
}

/**
 * ��ʼ���������������
 * */
void initEncoder() {
    initEncoderGPIO();
    initEncoderNVIC();
    initEncoderEXTI();
}
