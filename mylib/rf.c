//
// Created by Steven on 2019/12/9.
//

#include "rf.h"

#define RF()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)

void init_rf_gpio() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    //RF
    gpio.GPIO_Mode = GPIO_Mode_IN;
    gpio.GPIO_PuPd = GPIO_PuPd_UP;
    gpio.GPIO_Speed= GPIO_Speed_50MHz;
    gpio.GPIO_Pin  = GPIO_Pin_12;
    GPIO_Init(GPIOA, &gpio);
}

void delay_800_us() {
    uint32_t j = 1600;
    while (j--);
}

void delay_400_us() {
    uint32_t j = 800;
    while (j--);
}

void rf_receive_data(uint8_t data_array[], uint8_t max_length) {
    uint8_t count = 0;
    uint8_t i, j, byte;
    if(RF()) {
        //开始信号 12ms 高
        while (RF()) {
            delay_800_us();
            count++;
        }
        if(count >= 10) {
            while (RF());
        } else {
            return;
        }
        //开始接收数据
        for(i = 0; i < max_length; i++) {
            byte = 0;
            for(j = 0; j < 8; j++) {
                count = 0;
                while (!RF()) {
                    delay_800_us();
                    count++;
                }

                if(count > 3) {//停止信号
                    return;
                } else {
                    delay_400_us();
                    byte <<= 1;
                    if(RF()) {
                        byte |= 0x01;
                    }
                }
            }
            data_array[i] = byte;
        }
    }
}