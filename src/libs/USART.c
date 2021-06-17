#include "USART.h"

char buff;	// Variable para guardar dato entrante

/*
 *  Function: USART_Init
 *  -------------------------------------------
 *  @brief: Inicializacion del USART a partir de una
 *  velocidad de transmision
 *  @param: baud - velocidad en baudios
 */

void USART_Init(uint32_t baud) {
    
	// TODO
}

/*
 *  Function: USART_Putc    
 *  --------------------------------------
 *  @brief: Envia un unico byte por el USART
 *  @param: c - byte/caracter a enviar
 */

void USART_Putc(uint8_t c) {
    
	// TODO
}

/*
 *  Function: USART_Prints
 *  ---------------------------------------- 
 *  @brief: Envia una cadena de caracteres por USART
 *  @param: str - nadena a enviar
 */

void USART_Prints(const char *str) {
    
	// TODO
}

/*
 *  Function: USART_Printf 
 *  -------------------------------------------
 *  @brief: Envia un numero flotante por USART
 *  
 *  @param: f - numero flotante
 */

void USART_Printf(double var) {

    char *str = "";             // Array para guardar el float
    dtostrf(var,3,2,str);       // Conversion de float a string
    USART_Prints(str);           // Envio el string
}   

/*
 *  Funcion: ISR(USART_RX)
 *  --------------------------------------
 *  @brief: Servicio de interrupcion para USART RX  
 *  Complete. Se va a encargar de mandar por USART
 *  la informacion necesaria
 */

ISR(USART_RX_vect) {

	// TODO
}