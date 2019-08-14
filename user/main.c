#include "stm32f0xx.h"
#include "main.h"

void initAllDevices() {
    SystemInit();
    initMotorGPIO();    
    delayInit();
}

int main(void) {
    initAllDevices();
    forwardMotor(90.0);
    reverseMotor(90.0);
    while (1) {

    }
}
