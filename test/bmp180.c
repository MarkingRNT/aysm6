#include <util/delay.h>
#include "bmp180.h"
#include "I2C.h"

uint8_t bmp180ReadCalibrationData(Bmp180CalibrationData *data) {
    I2C_Init();
    I2C_Start();

    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_write);
    if (I2C_GetStatus() != write_address_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0xAA);
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_Stop();

    I2C_Start();
    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_read);
    if (I2C_GetStatus() != read_address_ack_sent) {
        return I2C_GetStatus();
    }

    for (int reg = 0xAA; reg <= 0xBE; reg += 2) {
        uint16_t bits = 0;
        uint8_t msb = I2C_ReadDataAck();
        if (I2C_GetStatus() != read_data_ack_sent) {
            return I2C_GetStatus();
        }

        uint8_t lsb;
        if (reg == 0xBE) {
            lsb = I2C_ReadDataNotAck();
            if (I2C_GetStatus() != read_data_ack_not_sent) {
                return I2C_GetStatus();
            }
        } else {
            lsb = I2C_ReadDataAck();
            if (I2C_GetStatus() != read_data_ack_sent) {
                return I2C_GetStatus();
            }
        }

        bits |= (msb << 8) | lsb;

        switch (reg) {
            case 0xAA:
                data->ac1 = bits;
                break;
            case 0xAC:
                data->ac2 = bits;
                break;
            case 0xAE:
                data->ac3 = bits;
                break;
            case 0xB0:
                data->ac4 = bits;
                break;
            case 0xB2:
                data->ac5 = bits;
                break;
            case 0xB4:
                data->ac6 = bits;
                break;
            case 0xB6:
                data->b1 = bits;
                break;
            case 0xB8:
                data->b2 = bits;
                break;
            case 0xBA:
                data->mb = bits;
                break;
            case 0xBC:
                data->mc = bits;
                break;
            case 0xBE:
                data->md = bits;
                break;
        }
    }

    I2C_Stop();

    return BMP180_OK;
}

uint8_t bmp180ReadUncompensatedTemperature(uint16_t *temperature) {
    I2C_Init();
    I2C_Start();

    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_write);
    if (I2C_GetStatus() != write_address_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0xF4);
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0x2E);
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_Stop();
    _delay_us(4500);

    I2C_Start();
    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_write);
    if (I2C_GetStatus() != write_address_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0xF6);
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_Stop();
    I2C_Start();
    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_read);
    if (I2C_GetStatus() != read_address_ack_sent) {
        return I2C_GetStatus();
    }

    uint8_t msb = I2C_ReadDataAck();
    if (I2C_GetStatus() != read_data_ack_sent) {
        return I2C_GetStatus();
    }

    uint8_t lsb = I2C_ReadDataNotAck();
    if (I2C_GetStatus() != read_data_ack_not_sent) {
        return I2C_GetStatus();
    }

    I2C_Stop();

    uint16_t result = 0;
    result |= (msb << 8) | lsb;

    *temperature = result;

    return BMP180_OK;
}

float bmp180CalculateTemperature(uint16_t uncompensatedTemperature, int32_t *b5, Bmp180CalibrationData *calibrationData) {
    int32_t x1 = ((uncompensatedTemperature - calibrationData->ac6) * (int32_t) calibrationData->ac5) >> 15;
    int32_t x2 = ((int32_t) calibrationData->mc << 11) / (x1 + calibrationData->md);
    *b5 = x1 + x2;
    float temperature = (int32_t) ((*b5 + 8) >> 4);
    temperature /= (float) 10;

    return temperature;
}

uint8_t bmp180ReadUncompensatedPressure(uint8_t oss, uint32_t *pressure) {
    
    I2C_Init();
    I2C_Start();
    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_write);
    if (I2C_GetStatus() != write_address_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0xF4);
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0x34 | (oss << 6));
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_Stop();

    switch (oss) {
        case BMP180_OSS_ULTRA_LOW_POWER:
            _delay_us(4500);
            break;
        case BMP180_OSS_STANDARD:
            _delay_us(7500);
            break;
        case BMP180_OSS_HIGH_RESOLUTION:
            _delay_us(13500);
            break;
        case BMP180_OSS_ULTRA_HIGH_RESOLUTION:
            _delay_us(25500);
            break;
    }

    I2C_Start();
    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_write);
    if (I2C_GetStatus() != write_address_ack_received) {
        return I2C_GetStatus();
    }

    I2C_SendData(0xF6);
    if (I2C_GetStatus() != write_data_ack_received) {
        return I2C_GetStatus();
    }

    I2C_Stop();
    I2C_Start();
    if (I2C_GetStatus() != start_transmitted) {
        return I2C_GetStatus();
    }

    I2C_SendSlaveAddress(BMP180_ADDRESS, i2c_read);
    if (I2C_GetStatus() != read_address_ack_sent) {
        return I2C_GetStatus();
    }

    uint8_t msb = I2C_ReadDataAck();
    if (I2C_GetStatus() != read_data_ack_sent) {
        return I2C_GetStatus();
    }

    uint8_t lsb = I2C_ReadDataAck();
    if (I2C_GetStatus() != read_data_ack_sent) {
        return I2C_GetStatus();
    }

    uint8_t xlsb = I2C_ReadDataNotAck();
    if (I2C_GetStatus() != read_data_ack_not_sent) {
        return I2C_GetStatus();
    }

    I2C_Stop();

    uint32_t result = 0;
    result |= ((uint16_t) msb << 8) | lsb;
    result <<= 8;
    result |= xlsb;

    result >>= (8 - oss);
    *pressure = result;

    return BMP180_OK;
}

long bmp180CalculatePressure(uint32_t uncompensatedPressure, int32_t *b5, uint8_t oss, Bmp180CalibrationData *calibrationData) {
    int32_t b6 = *b5 - 4000;
    int32_t x1 = ((int32_t) calibrationData->b2 * (b6 * b6 >> 12)) >> 11;
    int32_t x2 = (int32_t) calibrationData->ac2 * b6 >> 11;
    int32_t x3 = x1 + x2;
    int32_t b3 = ((((int32_t) calibrationData->ac1 * 4 + x3) << oss) + 2) >> 2;
    x1 = (int32_t) calibrationData->ac3 * b6 >> 13;
    x2 = ((int32_t) calibrationData->b1 * (b6 * b6 >> 12)) >> 16;
    x3 = ((x1 + x2) + 2) >> 2;
    uint32_t b4 = (uint32_t) calibrationData->ac4 * (x3 + 32768) >> 15;
    uint32_t b7 = ((uncompensatedPressure - b3) * (50000 >> oss));

    long p;
    if (b7 < 0x80000000) {
        p = ((b7 * 2) / b4);
    } else {
        p = ((b7 / b4) * 2);
    }

    x1 = (p >> 8) * (p >> 8);
    x1 = (x1 * 3038) >> 16;
    x2 = (-7357 * p) >> 16;
    p = p + ((x1 + x2 + 3791) >> 4);

    return p;
}

uint8_t bmp180ReadData(uint8_t oss, Bmp180Data *data, Bmp180CalibrationData *calibrationData) {
    uint16_t ut;
    uint8_t result = bmp180ReadUncompensatedTemperature(&ut);

    if (result != BMP180_OK) {
        return BMP180_ERROR_UT;
    }

    uint32_t up;
    result = bmp180ReadUncompensatedPressure(oss, &up);

    if (result != BMP180_OK) {
        return BMP180_ERROR_UP;
    }

    int32_t b5 = 0;

    data->temperatureC = bmp180CalculateTemperature(ut, &b5, calibrationData);
    data->pressurePa = bmp180CalculatePressure(up, &b5, oss, calibrationData);

    return BMP180_OK;
}

float bmp180ConvertPressurePaToMmHg(long pressurePa) {
    return (float) (pressurePa * 0.00750062);
}
