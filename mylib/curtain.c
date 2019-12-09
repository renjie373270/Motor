//
// Created by Steven on 2019/12/6.
//

#include "curtain.h"

#define CURTAIN_0() GPIO_ResetBits(GPIOB, GPIO_Pin_15)
#define CURTAIN_1() GPIO_SetBits(GPIOB, GPIO_Pin_15)
#define CURTAIN_POWER_ON() GPIO_ResetBits(GPIOA, GPIO_Pin_12)
#define CURTAIN_POWER_OFF() GPIO_SetBits(GPIOA, GPIO_Pin_12)

void init_curtain_gpio() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType= GPIO_OType_PP;
    gpio.GPIO_Speed= GPIO_Speed_50MHz;
    gpio.GPIO_Pin  = GPIO_Pin_15;
    GPIO_Init(GPIOB, &gpio);

    gpio.GPIO_Pin  = GPIO_Pin_12;
    gpio.GPIO_OType= GPIO_OType_OD;
    gpio.GPIO_Speed= GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio);
}

void delay_us_800() {
    uint32_t j = 1600;
    while (j--);
}

void start_transfer() {
    CURTAIN_1();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
}

void send_1() {
    CURTAIN_0();
    delay_us_800();
    CURTAIN_1();
    delay_us_800();
    delay_us_800();
    delay_us_800();
}

void send_0() {
    CURTAIN_0();
    delay_us_800();
    CURTAIN_1();
    delay_us_800();
}

void stop_transfer() {
    send_0();
    CURTAIN_0();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    delay_us_800();
    CURTAIN_0();
}

void send_remote_data(uint8_t dataArray[], uint8_t length) {
    uint8_t i, j, byte;
    CURTAIN_POWER_ON();
    start_transfer();
    for(i = 0; i < length; i++) {
        byte = dataArray[i];
        for(j = 0; j < 8; j++) {
            if(byte & 0x80) {
                send_1();
            } else {
                send_0();
            }
            byte <<= 1;
        }
    }
    stop_transfer();
    CURTAIN_POWER_OFF();
}

void send_curtain_data(uint8_t data_array[], uint8_t length) {
    send_remote_data(data_array, length);
}

void close_curtain() {
    uint8_t data_array[] = {0xB2, 0x72, 0x06};
    send_curtain_data(data_array, 3);
    send_curtain_data(data_array, 3);
    send_curtain_data(data_array, 3);
}

void open_curtain() {
    uint8_t data_array[] = {0xB2, 0x72, 0x05};
    send_curtain_data(data_array, 3);
    send_curtain_data(data_array, 3);
    send_curtain_data(data_array, 3);
}

void stop_curtain() {
    uint8_t data_array[] = {0xB2, 0x72, 0x07};
    send_curtain_data(data_array, 3);
    send_curtain_data(data_array, 3);
    send_curtain_data(data_array, 3);
}

void init_curtain() {
    init_curtain_gpio();
}