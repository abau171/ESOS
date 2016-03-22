#define UARTFR 0x06
#define UARTFR_TXFF 0x20

#include <device_types.h>
#include <uart.h>

void uart_print(uart_address_t addr, char* string) {
	while (*string != 0) {
		while (*(addr + UARTFR) & UARTFR_TXFF);
		*addr = *string;
		string++;
	}
}

