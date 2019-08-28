//
// Created by Steven on 2019/8/27.
//

#include "display.h"

#define  SEG_DS_PORT GPIOA
#define  SEG_DS_PIN  GPIO_Pin_10
#define  SEG_DS_RCC RCC_AHBPeriph_GPIOA

#define  SEG_ST_PORT GPIOA
#define  SEG_ST_PIN  GPIO_Pin_11
#define  SEG_ST_RCC RCC_AHBPeriph_GPIOA

#define  SEG_SH_PORT GPIOA
#define  SEG_SH_PIN  GPIO_Pin_12
#define  SEG_SH_RCC RCC_AHBPeriph_GPIOA


/**
 * 初始化数码管相关IO口
 * */
void initSegGPIO() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(SEG_SH_RCC | SEG_DS_RCC | SEG_ST_RCC, ENABLE);

    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType= GPIO_OType_PP;
    gpio.GPIO_Speed= GPIO_Speed_10MHz;

    gpio.GPIO_Pin  = SEG_SH_PIN;
    GPIO_Init(SEG_SH_PORT, &gpio);

    gpio.GPIO_Pin  = SEG_DS_PIN;
    GPIO_Init(SEG_DS_PORT, &gpio);

    gpio.GPIO_Pin  = SEG_ST_PIN;
    GPIO_Init(SEG_ST_PORT, &gpio);
}


/**
 * 设置 74HC595 内容
 * 先发送高字节、高位
 * */
void sendBytesTo595(uint8_t bytes[], uint8_t length) {
    uint8_t i, j, ds, byte;
    for(i = 0; i < length; i++) {
        byte = bytes[length - 1 - i];
        for(j = 0; j < 8; j++) {
            ds = (byte & 0x80) > 0;
            if(ds) {
                GPIO_SetBits(SEG_DS_PORT, SEG_DS_PIN);
            } else {
                GPIO_ResetBits(SEG_DS_PORT, SEG_DS_PIN);
            }
            byte <<= 1;
            GPIO_ResetBits(SEG_SH_PORT, SEG_SH_PIN);
            GPIO_SetBits(SEG_SH_PORT, SEG_SH_PIN);
        }
    }
    GPIO_ResetBits(SEG_ST_PORT, SEG_ST_PIN);
    GPIO_SetBits(SEG_ST_PORT, SEG_ST_PIN);
}

/**
 * 设置显示内容
 * */
void display(uint8_t num1, uint8_t num2) {
    uint8_t bytes[2] = {0}, length = 2;
    uint8_t segTable[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

    bytes[0] = 1 << 1;
    bytes[1] = ~segTable[num1];
    sendBytesTo595(bytes, length);
    delayInMilliSeconds(5);

    bytes[0] = 1 << 2;
    bytes[1] = ~segTable[num2];
    sendBytesTo595(bytes, length);
    delayInMilliSeconds(5);
}

/**
 * 初始化数码管
 * */
void initDisplayDevice() {
    initSegGPIO();
}
