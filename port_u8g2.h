#ifndef PORT_U8G2_H
#define PORT_U8G2_H
#include "u8g2.h"
uint8_t u8g2_gpio_and_delay(u8x8_t*u8x8,uint8_t msg,uint8_t arg_int,void* arg_ptr);
uint8_t u8x8_byte_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
#endif