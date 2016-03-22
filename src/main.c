#include <device_addresses.h>
#include <uart.h>
#include <timer.h>

void main() {
	uart_print(DEV_UART0, "ESOS reboot\n");
	while (1) {
		timer_usleep(DEV_TIMER0, 1000000);
		uart_print(DEV_UART0, "tick");
	}
}

