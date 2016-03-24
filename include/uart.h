#ifndef UART_H
#define UART_H

#include <device_types.h>

void uart_cprint(uart_address_t addr, char c);

void uart_print(uart_address_t addr, char* string);

void uart_dprint(uart_address_t addr, unsigned int a);

#endif

