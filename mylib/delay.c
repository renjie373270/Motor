//
// Created by Steven on 2019/8/14.
//

#include "delay.h"

uint32_t sysTickCountDown = 0;

/**
 * ������ʱ
 * */
void delayInMilliSeconds(uint32_t x) {
    sysTickCountDown = x;
    while (sysTickCountDown != 0);
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
