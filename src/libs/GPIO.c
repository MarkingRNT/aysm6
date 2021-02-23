#include "GPIO.h"

extern float sp, temp;

/*****************************************************
    Inicializa los puertos digitales para el PWM
    y para usar una interrupcion externa
*****************************************************/

void GPIO_Init(void) {

    EICRA = 0x03;       // INT0 con flanco ascendente
    EIMSK = 1 << INT0;  // Habilitada la interrupcion INT0
    DDRB |= 1 << PB1 | 1 << PB2;    // Pines de PWM como salida
}

/*****************************************************
    Servicio de interrupcion para External 
    Interrupt 0. Se va a encargar de mandar por UART
    la informacion necesaria
*****************************************************/

ISR(INT0_vect) {
    
    // TODO
}