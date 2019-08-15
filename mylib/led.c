//
// Created by Steven on 2019/8/15.
//

#include "led.h"


void ledInit() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE);

    gpio.GPIO_Pin  = GPIO_Pin_11;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType= GPIO_OType_PP;
    gpio.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);
}

void ledOn() {
    GPIO_SetBits(GPIOA, GPIO_Pin_11);
}

void ledOff() {
    GPIO_ResetBits(GPIOA, GPIO_Pin_11);
}
