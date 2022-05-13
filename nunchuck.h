#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include <stdint.h>

#define NUNCHUCK_I2C_ADDRESS    0x52

typedef uint8_t (*nunchuck_receive_fptr)(uint16_t address, uint8_t *data, uint32_t length);
typedef uint8_t (*nunchuck_transmit_fptr)(uint16_t address, uint8_t *data, uint32_t length);
typedef uint8_t (*nunchuck_check_bus_fptr)(uint16_t address);

enum nunchuck_return_code {
    NCHUCK_OK,
    NCHUCK_ERROR,
};

struct nunchuck {
    nunchuck_receive_fptr receive;
    nunchuck_transmit_fptr transmit;
    nunchuck_check_bus_fptr check_bus;

    int8_t accX;
    int8_t accY;
    int8_t accZ;

    uint8_t joyX;
    uint8_t joyY;

    uint8_t buttonC;
    uint8_t buttonZ;
};

uint8_t nunchuck_init(struct nunchuck *dev);
uint8_t nunchuck_update(struct nunchuck *dev);

#endif