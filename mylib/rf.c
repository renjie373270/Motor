//
// Created by Steven on 2019/12/9.
//

#include "rf.h"

uint8_t rf_data_buffer[16] = {0};
uint8_t data_size = 0;

void init_rf_gpio() {
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI4_15_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource12);
    EXTI_InitStruct.EXTI_Line = EXTI_Line12;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStruct);
}

void delay_100_us() {
    uint32_t i = 250;
    while(i--);
}

void rf_receive_data() {
    uint8_t count = 0;
    uint8_t i, j, byte;
    if(RF()) {
        //开始信号 12ms 高
        while (RF()) {
            delay_100_us();
            count++;
        }
        if(count < 80) {
            return;
        }
        
        //开始接收数据
        for(i = 0; i < 16; i++) {
            byte = 0;
            for(j = 0; j < 8; j++) {
                count = 0;
                while (!RF()) {
                    delay_100_us();
                    count++;
                }

                if(count > 15) {//停止信号
                    return;
                }
                count = 0;
                while (RF()) {
                    delay_100_us();
                    count++;
                }
                byte <<= 1;
                if(count > 16) {
                    byte |= 0x01;
                }
            }
            if(i == 0 && byte != 0xB2) {
                return;
            }
            rf_data_buffer[i] = byte;
            data_size = i + 1;
        }
    }
}

uint8_t rf_read_data(uint8_t *data_array) {
    uint8_t i, length;
    if(data_size > 0) {
        length = data_size;
        for(i = 0; i < data_size; i++) {
            data_array[i] = rf_data_buffer[i];
            rf_data_buffer[i] = 0;
        }
        data_size = 0;
        return length;
    }
}