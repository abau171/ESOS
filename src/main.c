#include <scheduler.h>
#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>

void main(void) {
	uart_print(DEV_UART0, "ESOS reboot\n");
	init_scheduler();
	schedule_next_task();
	activate_task();
}

void handle_syscall(void) {
	uart_print(DEV_UART0, "syscall!\n");
	schedule_next_task();
}

