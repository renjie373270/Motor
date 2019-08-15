//
// Created by Steven on 2019/8/14.
//

#include "delay.h"

/**
 * 毫秒延时
 * */
void delayInMilliSeconds(uint32_t x) {
    vTaskDelay(x);
}

/**
 * 系统定时器初始化
 * 定时时间1 ms
 * */
void sysTickInit(void){
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Config(SystemCoreClock / 1000);
}

/**
 * 硬件延时模块初始化
 * */
void delayInit() {
    sysTickInit();
}
