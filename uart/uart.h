#ifndef __UART_H
#define	__UART_H

#include "stm32f0xx.h"
#include <stdio.h>

#define UART_TX_BUFFER_SIZE        255
#define UART_RX_BUFFER_SIZE        255

void serial_open(uint8_t port, uint32_t baud);
uint8_t serial_write_buf(uint8_t* buf, uint16_t length);
uint8_t serial_read_ch(void);
uint16_t serial_free(void);
uint16_t serial_available(void);

#endif /* __UART_H */



