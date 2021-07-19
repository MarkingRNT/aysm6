#include <avr/io.h>
#include "LCD.h"
#include "bmp180.h"
#include <util/delay.h>

int main (void) {

    LCD_Init();
    Bmp180CalibrationData calibrationData;
    uint8_t result = bmp180ReadCalibrationData(&calibrationData);
    Bmp180Data bmp180Data;

    while (1) {

        if (result == BMP180_OK) {
            
            LCD_Clear();
            LCD_WriteString("OK");
            _delay_ms(500);
            result = bmp180ReadData(BMP180_OSS_STANDARD, &bmp180Data, &calibrationData);

            if (result == BMP180_OK) {
                long pressure = bmp180Data.pressurePa;
                LCD_Clear();
                LCD_WriteLong(pressure);
            }
        }
        else {
            LCD_Clear();
            LCD_WriteLong(result);
        }
        _delay_ms(500);
    }

    return 0;
}