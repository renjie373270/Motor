//
// Created by Steven on 2019/8/15.
//

#include "led.h"


#define  LED_RCC_PORT  RCC_AHBPeriph_GPIOB
#define  LED_PORT      GPIOB
#define  LED_PIN       GPIO_Pin_12

void ledInit() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(LED_RCC_PORT, ENABLE);

    gpio.GPIO_Pin  = LED_PIN;
    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType= GPIO_OType_PP;
    gpio.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(LED_PORT, &gpio);
}

void ledOn() {
    GPIO_SetBits(LED_PORT, LED_PIN);
}

void ledOff() {
    GPIO_ResetBits(LED_PORT, LED_PIN);
}
