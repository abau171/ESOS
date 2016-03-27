#include <timer.h>
#include <scheduler.h>
#include <device_addresses.h>
#include <uart.h>

/* the current task will resume after each of these funtions returns */

void kernel_init(void) {
	uart_print(DEV_UART0, "ESOS reboot\n");
	/* initialize the scheduler so tasks can be created and managed */
	init_scheduler();
	/* start timer loop (ticks every 1 second) */
	timer_loop(DEV_TIMER0, 1000000);
	schedule_next_task();
}

void handle_syscall(void) {
	uart_print(DEV_UART0, "syscall!\n");
	schedule_next_task();
}

void handle_interrupt(void) {
	uart_print(DEV_UART0, "interrupt!\n");
	/* need to clear interrupt source if it is handled */
	timer_clear(DEV_TIMER0);
	schedule_next_task();
}

