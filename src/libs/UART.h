#ifndef _UART_H_
#define _UART_H_

#include <stdlib.h>
#include <avr/io.h>

/*  Macros  */
// Agreguen las macros que vean convenientes

/*  Prototipos de funciones  */
void UART_Init(uint32_t baud);
void UART_Putc(uint8_t c);
void UART_Prints(const char *str);
void UART_Printf(double f);

#endif /* _UART_H_ */