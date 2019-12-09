//
// Created by Steven on 2019/12/9.
//

#ifndef MOTOR_RF_H
#define MOTOR_RF_H

#include "main.h"

#define RF()   GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_12)

void init_rf_gpio(void);
void rf_receive_data();
uint8_t rf_read_data(uint8_t *data_array);

#endif //MOTOR_RF_H
