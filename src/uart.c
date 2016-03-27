#define UARTFR 0x06
#define UARTFR_TXFF 0x20

#include <device_types.h>
#include <uart.h>

void uart_cprint(uart_address_t addr, char c) {
	/* wait for uart to be ready to recieve a character */
	while (*(addr + UARTFR) & UARTFR_TXFF);
	/* write the character to the uart */
	*addr = c;
}

void uart_print(uart_address_t addr, char* string) {
	while (*string != 0) {
		uart_cprint(addr, *string);
		string++;
	}
}

void uart_bprint(uart_address_t addr, unsigned int a) {
	unsigned int mask = 1 << 31;
	for (int i = 0; i < 32; i++) {
		if ((a & mask) == 0) {
			uart_cprint(addr, '0');
		} else {
			uart_cprint(addr, '1');
		}
		mask >>= 1;
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

void uart_xprint(uart_address_t addr, unsigned int a) {
	if (a == 0) {
		uart_cprint(addr, '0');
	} else {
		unsigned int next = a / 16;
		if (next != 0) uart_xprint(addr, next);
		char part = a % 16;
		if (part < 10) {
			uart_cprint(addr, 48 + part);
		} else {
			uart_cprint(addr, 87 + part);
		}
	}
}

