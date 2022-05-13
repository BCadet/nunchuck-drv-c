#include "nunchuck.h"

uint8_t nunchuck_init(struct nunchuck *dev)
{
    uint8_t result;
    result = dev->check_bus((uint16_t)(NUNCHUCK_I2C_ADDRESS<<1));
    if (result == NCHUCK_OK)
    {
        uint8_t init[2] = {0xF0, 0x55};
        result = dev->transmit((uint16_t)(NUNCHUCK_I2C_ADDRESS<<1), init, 2);
        init[0] = 0xFB;
        init[1] = 0x00;
        result |= dev->transmit((uint16_t)(NUNCHUCK_I2C_ADDRESS<<1), init, 2);
        init[0] = 0;
        result |= dev->transmit((uint16_t)(NUNCHUCK_I2C_ADDRESS<<1), init, 1);
    }
    return result;
}

uint8_t nunchuck_update(struct nunchuck *dev)
{
    uint8_t result;
    uint8_t data[6];

    result = dev->receive((uint16_t)(NUNCHUCK_I2C_ADDRESS<<1), data, 6);

    if(result == NCHUCK_OK)
    {
        dev->joyX = data[0];
        dev->joyY = data[1];
        dev->accX = (data[2] << 2) | ((data[5] >> 2) & 0x03);
        dev->accY = (data[3] << 2) | ((data[5] >> 4) & 0x03);
        dev->accZ = (data[4] << 2) | ((data[5] >> 6) & 0x03);
        dev->buttonC = !((data[5]&0x02)>>1);
        dev->buttonZ = !(data[5]&0x01);

        data[0] = 0;
        result |= dev->transmit((uint16_t)(NUNCHUCK_I2C_ADDRESS<<1), data, 1);
    }

    return result;
}
