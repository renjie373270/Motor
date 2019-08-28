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
    uint8_t i, shi, ge, count = 0;
    while (1) {
        count ++;
        if(count > 99)
            count = 0;
        shi = count / 10;
        ge = count % 10;
        i = 100;
        while (i--)
            display(shi, ge);
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

    }
}

int main(void) {
    initAllDevices();
    xTaskCreate(SegTask, "SegTask", 128, NULL, 200, &SegTask_Handle);
    xTaskCreate(MotorTask, "MotorTask", 128, NULL, 200, &MotorTask_Handle);
    xTaskCreate(WatchDogTask, "WatchDogTask", 128, NULL, 200, &WatchDogTask_Handle);
    vTaskStartScheduler();
    while(1);
}
