#include "main.h"

static TaskHandle_t DisplayTask_Handle = NULL;
static TaskHandle_t MotorTask_Handle = NULL;
static TaskHandle_t WatchDogTask_Handle = NULL;
static TaskHandle_t EncoderTask_Handle = NULL;

void initAllDevices() {
    SystemInit();
    delayInit();
//    initDisplayDevice();
//    initMotorGPIO();
//    initEncoder();
    init_curtain();
}

static void TestTask(void *parameter) {
    open_curtain();
    delayInMilliSeconds(3000);
    close_curtain();
    delayInMilliSeconds(3000);
    stop_curtain();
    while (1) {
        delayInMilliSeconds(1000);
    }
}

int main() {
    initAllDevices();
    xTaskCreate(TestTask, "TestTask", 128, NULL, 200, NULL);
    vTaskStartScheduler();
    while(1);
}

/**
 * 显示任务
 * */
static void DisplayTask(void *parameter) {
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
 * 电机转动任务y
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

/**
 * 编码器检测任务
 * */
static void EncoderTask(void *parameter) {
    while (1) {
        readEncoderStatus();
    }
}

//int main(void) {
//    initAllDevices();
//    xTaskCreate(EncoderTask, "EncoderTask", 128, NULL, 200, &EncoderTask_Handle);
//    xTaskCreate(DisplayTask, "DisplayTask", 128, NULL, 199, &DisplayTask_Handle);
//    xTaskCreate(MotorTask,   "MotorTask", 128, NULL, 198, &MotorTask_Handle);
//    xTaskCreate(WatchDogTask, "WatchDogTask", 128, NULL, 197, &WatchDogTask_Handle);
//    vTaskStartScheduler();
//    while(1);
//}
