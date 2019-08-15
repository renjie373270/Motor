#include "main.h"

static TaskHandle_t LEDTask_Handle = NULL;
static TaskHandle_t MotorTask_Handle = NULL;
static TaskHandle_t WatchDogTask_Handle = NULL;

void initAllDevices() {
    SystemInit();
    delayInit();
    ledInit();
}

/**
 * ��������
 * */
static void LedTask(void *parameter) {
    while (1) {
        ledOn();
        delayInMilliSeconds(200);
        ledOff();
        delayInMilliSeconds(200);
    }
}

/**
 * ���ת������
 * */
static void MotorTask(void *parameter) {
    while (1) {

    }
}

/**
 * ���Ź�����
 * */
 static void WatchDogTask(void *parameter) {
     while (1) {

     }
 }

int main(void) {
    initAllDevices();
    xTaskCreate((TaskFunction_t )LedTask, "LedTask", 128, NULL, 200, &LEDTask_Handle);
    xTaskCreate((TaskFunction_t )MotorTask, "MotorTask", 128, NULL, 200, &MotorTask_Handle);
    xTaskCreate((TaskFunction_t )WatchDogTask, "WatchDogTask", 128, NULL, 200, &WatchDogTask_Handle);
    vTaskStartScheduler();
    while(1);
}
