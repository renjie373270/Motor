//
// Created by Steven on 2019/8/14.
//

#include "motor.h"
#include "math.h"

#define MOTOR_DELAY() delayInMilliSeconds(2)

int8_t  positionArray[5] = {0, 0, 0, 0, 0};
uint8_t confirmArray[5] = {FALSE, FALSE, FALSE, FALSE, FALSE};

uint8_t numberOf595 = 2; //595寄存器数量
uint8_t motorBytes[2] = {0xFF, 0xFF};
uint8_t runTable[9] = {0x0E, 0x0A, 0x0B, 0x09, 0x0D, 0x05, 0x07, 0x06};//8拍


/**
 * 初始化步进电机相关IO口
 * */
void initMotorGPIO() {
    GPIO_InitTypeDef gpio;
    RCC_AHBPeriphClockCmd(MOTOR_SH_RCC | MOTOR_DS_RCC | MOTOR_ST_RCC, ENABLE);

    gpio.GPIO_Mode = GPIO_Mode_OUT;
    gpio.GPIO_OType= GPIO_OType_PP;
    gpio.GPIO_Speed= GPIO_Speed_10MHz;

    gpio.GPIO_Pin  = MOTOR_SH_PIN;
    GPIO_Init(MOTOR_SH_PORT, &gpio);

    gpio.GPIO_Pin  = MOTOR_DS_PIN;
    GPIO_Init(MOTOR_DS_PORT, &gpio);

    gpio.GPIO_Pin  = MOTOR_ST_PIN;
    GPIO_Init(MOTOR_ST_PORT, &gpio);
}

/**
 * 设置 74HC595 内容
 * 先发送高字节、高位
 * */
void sendBytesToMotor595(uint8_t bytes[], uint8_t length) {
    uint8_t i, j, byte, ds;
    for(i = 0; i < length; i++) {
        byte = bytes[length - 1 - i];
        for(j = 0; j < 8; j++) {
            ds = (byte & 0x80) > 0;
            if(ds) {
                GPIO_SetBits(MOTOR_DS_PORT, MOTOR_DS_PIN);
            } else {
                GPIO_ResetBits(MOTOR_DS_PORT, MOTOR_DS_PIN);
            }
            byte <<= 1;
            GPIO_ResetBits(MOTOR_SH_PORT, MOTOR_SH_PIN);
            GPIO_SetBits(MOTOR_SH_PORT, MOTOR_SH_PIN);
        }
    }
    GPIO_ResetBits(MOTOR_ST_PORT, MOTOR_ST_PIN);
    GPIO_SetBits(MOTOR_ST_PORT, MOTOR_ST_PIN);
}

/**
 * 顺时针转动，每次一圈
 * */
void forward(uint8_t motorIndex) {
		uint8_t i;
    for(i = 0; i < 8; i++) {
        motorBytes[motorIndex] = runTable[i] << 1;
        sendBytesToMotor595(motorBytes, numberOf595);
        MOTOR_DELAY();
    }
}

/**
 * 逆时针转动，每次一圈
 * */
void reverse(uint8_t motorIndex) {
	uint8_t i;
    for(i = 0; i < 8; i++) {
        motorBytes[motorIndex] = runTable[7 - i] << 1;
        sendBytesToMotor595(motorBytes, numberOf595);
        MOTOR_DELAY();
    }
}


/**
 * 正向转动，输入参数为角度
 * 步距角18度，减速比1:275
 * */
void forwardMotor(uint8_t motorIndex, int8_t *temp) {
    float stepAngle = 18 / 275.0;
    float degrees = (*temp) * 1.0;
    uint32_t remainSteps = degrees / stepAngle;
    uint32_t circles = remainSteps / 4;
    while (circles--) {
        if(circles % (*temp) == 0)
            (*temp) --;
        forward(motorIndex);
    }
    motorBytes[motorIndex] = 0xFF;
    sendBytesToMotor595(motorBytes, numberOf595);
}

/**
 * 反向转动
 * */
void reverseMotor(uint8_t motorIndex, int8_t *temp) {
    float stepAngle = 18 / 275.0;
    float degrees = -(*temp) * 1.0;
    uint32_t remainSteps = degrees / stepAngle;
    uint32_t circles = remainSteps / 4;
    while (circles--) {
        if(circles % (*temp) == 0)
            (*temp) --;
        reverse(motorIndex);
    }
    motorBytes[motorIndex] = 0xFF;
    sendBytesToMotor595(motorBytes, numberOf595);
}

/**
 * 电机位置更新
 * */
void updateMotorPosition() {
    uint8_t i;
    for(i = 0; i < 5; i++) {
        if(confirmArray[i] == TRUE) {
            if(positionArray[i] > 0) {
                forwardMotor(i, &positionArray[i]);
            } else {
                reverseMotor(i, &positionArray[i]);
            }
            confirmArray[i] = FALSE;
            positionArray[i] = 0;
        }
    }
}
 