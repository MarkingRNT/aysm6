#include "UART.h"

/*********************************************
    Inicializacion del UART a partir de una
    velocidad de transmision
*********************************************/

void UART_Init(uint32_t baud) {
    
    // TODO
}

/********************************************
    Envia un unico byte por el UART
********************************************/

void UART_Putc(uint8_t c) {
    
    // TODO
}

/********************************************
    Envia una cadena de caracteres por UART
********************************************/

void UART_Prints(const char *str) {
    
    // TODO
}

/********************************************
    Envia un numero flotante por UART
********************************************/

void UART_Printf(double f) {

    char str[20];           // Array para guardar el float
    dtostrf(f,3,2,str);     // Conversion de float a string
    UART_Prints(str);       // Envio el string
}   