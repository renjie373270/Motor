#include "main.h"

static TaskHandle_t SegTask_Handle = NULL;
static TaskHandle_t MotorTask_Handle = NULL;
static TaskHandle_t WatchDogTask_Handle = NULL;

void initAllDevices() {
    SystemInit();
    delayInit();
    initDisplayDevice();
    initMotorGPIO();
    initEncoder();
}

/**
 * 显示任务
 * */
static void SegTask(void *parameter) {
    int8_t num1, num2;
    while (1) {
        num1 = positionArray[0];
        num2 = positionArray[1];
        if(num1 < 0) {
            num1 = -num1;
        }
        if(num2 < 0) {
            num2 = -num2;
        }
        num1 %= 10;
        num2 %= 10;
        display(num2, num1);
    }
}

/**
 * 电机转动任务
 * */
static void MotorTask(void *parameter) {
    while (1) {
        updateMotorPosition();
    }
}

/**
 * 看门狗任务
 * */
static void WatchDogTask(void *parameter) {
    while (1) {
        delayInMilliSeconds(100);
    }
}

int main(void) {
    initAllDevices();
    xTaskCreate(SegTask, "SegTask", 128, NULL, 200, &SegTask_Handle);
    xTaskCreate(MotorTask, "MotorTask", 256, NULL, 200, &MotorTask_Handle);
    xTaskCreate(WatchDogTask, "WatchDogTask", 128, NULL, 200, &WatchDogTask_Handle);
    vTaskStartScheduler();
    while(1);
}
