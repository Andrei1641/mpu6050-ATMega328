#include <avr/io.h>
#include "mpu/i2cInterface.h"
#include "I2C/i2c.h"
#include "UART/uart.h"
#include "mpu/mpuCommands/mpu.h"

#define FOSC 16000000UL
#define BAUD 9600
#define UBRR FOSC/16/BAUD-1

const struct i2cInterface i2c = {
    .start = start,
    .repeatedStart = repeatedStart,
    .readBytes = readBytes,
    .writeBytes = writeBytes,
    .setAddressWrite = setAddressWrite,
    .requestRegister = requestRegister,
    .setAddressRead = setAddressRead,
    .stop = stop,
    .read = read,
    .write = write
};

void byteToHex(uint8_t b, char returnHex[2])
{
    char hex[] = "0123456789ABCDEF";
    returnHex[0] = hex[b >> 4];
    returnHex[1] = hex[b & 0x0F];
}

int main(void)
{
    USART_Init(UBRR);
    initGyro(&i2c);
    
    uint8_t xyzGyro[6];

    while(1)
    {
        readGyro(&i2c, xyzGyro);
        char tmpHex[2];
        USART_TransmitString("x: ", 2);
        byteToHex(xyzGyro[0], tmpHex);
        USART_TransmitString(tmpHex, 2);
        byteToHex(xyzGyro[1], tmpHex);
        USART_TransmitString(tmpHex, 2);

        USART_TransmitString("      ", 2);

        USART_TransmitString("y: ", 2);
        byteToHex(xyzGyro[2], tmpHex);
        USART_TransmitString(tmpHex, 2);
        byteToHex(xyzGyro[3], tmpHex);
        USART_TransmitString(tmpHex, 2);

        USART_TransmitString("      ", 2);

        USART_TransmitString("z: ", 2);
        byteToHex(xyzGyro[4], tmpHex);
        USART_TransmitString(tmpHex, 2);
        byteToHex(xyzGyro[5], tmpHex);
        USART_TransmitString(tmpHex, 2);

        USART_TransmitString("\r\n", 2);
    }
}
