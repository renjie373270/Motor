#include "main.h"

void initAllDevices() {
    SystemInit();
    initMotorGPIO();    
    delayInit();
    initEncoder();
}

int main(void) {
    initAllDevices();
//    forwardMotor(90.0);
//    reverseMotor(90.0);
    while (1) {
        updateMotorPosition();
    }
}
