//
// Created by Steven on 2019/12/9.
//

#ifndef MOTOR_RF_H
#define MOTOR_RF_H

#include "main.h"

void init_rf_gpio(void);
void rf_receive_data(uint8_t data_array[], uint8_t max_length);

#endif //MOTOR_RF_H
