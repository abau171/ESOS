#define UARTFR 0x06
#define UARTFR_TXFF 0x20

#include <device_types.h>
#include <uart.h>

void uart_cprint(uart_address_t addr, char c) {
	while (*(addr + UARTFR) & UARTFR_TXFF);
	*addr = c;
}

void uart_print(uart_address_t addr, char* string) {
	while (*string != 0) {
		uart_cprint(addr, *string);
		string++;
	}
}

void uart_dprint(uart_address_t addr, unsigned int a) {
	if (a == 0) {
		uart_cprint(addr, '0');
	} else {
		unsigned int next = a / 10;
		if (next != 0) uart_dprint(addr, next);
		char part = a % 10;
		uart_cprint(addr, 48 + part);
	}
}

