#include <avr/io.h>
#include "I2C.h"

void I2C_Init(void) {
    
    // TODO
}

void I2C_Wait(void) {
    
    // TODO
}

void I2C_Start(void) {
    
    // TODO
    I2C_Wait();
}

void I2C_Stop(void) {
    
    // TODO
}

void I2C_SendData(uint8_t data) {
    
    // TODO
    I2C_Wait();
}

uint8_t I2C_ReadDataAck(void) {
    
    // TODO
    I2C_Wait();
    return;
}

uint8_t I2C_ReadDataNotAck(void) {

    // TODO 
    I2C_Wait();
    return;
}

void I2C_SendSlaveAddress(uint8_t address, uint8_t readWriteMode) {
    
    // TODO
}

uint8_t I2C_GetStatus(void) {

    // TODO
    return;
}