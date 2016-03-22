#include <bootstrap.h>
#include <device_addresses.h>
#include <uart.h>
#include <timer.h>

unsigned int stack[256];

void user_f() {
	uart_print(DEV_UART0, "user\n");
	timer_usleep(DEV_TIMER0, 1000000);
	uart_print(DEV_UART0, "user done, resetting...\n");
	svc();
}

void main() {
	uart_print(DEV_UART0, "ESOS reboot\n");
	unsigned int* stack_start = &stack[256 - 16];
	stack_start[0] = 0x10;
	stack_start[1] = (unsigned int) &user_f;
	activate(stack_start);
}

