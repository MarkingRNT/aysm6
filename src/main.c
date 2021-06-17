#include <avr/io.h>
#include "libs/foo.h"
#include <string.h>

extern int volatile adc;
extern float temp, sp;
extern char buff;

int main (void) {

    // Inicializacion de los perifericos
    MCU_Init();

    while (1) {
    
        if (adc) {
            // Si hubo una lectura, tomo el dato y convierto las unidades
            ADC_conversion();   
            adc = 0;
        }
        // Generar PWM dependiendo de la temperatura y setpoint
        PWM(temp, sp);

        // TODO

    }
    return 0;
}