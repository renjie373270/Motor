//
// Created by Steven on 2019/8/14.
//

#include "delay.h"

/**
 * ������ʱ
 * */
void delayInMilliSeconds(uint32_t x) {
    vTaskDelay(x);
}

/**
 * ϵͳ��ʱ����ʼ��
 * ��ʱʱ��1 ms
 * */
void sysTickInit(void){
    SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
    SysTick_Config(SystemCoreClock / 1000);
}

/**
 * Ӳ����ʱģ���ʼ��
 * */
void delayInit() {
    sysTickInit();
}
