#include <timer.h>
#include <scheduler.h>
#include <device_addresses.h>
#include <uart.h>

/* the current task will resume after each of these funtions returns */

void kernel_init(void) {
	uart_print(DEV_UART0, "ESOS reboot\n");
	/* initialize the task list */
	init_task();
	/* initialize the scheduler so tasks can be created and managed */
	init_scheduler();
	/* start timer loop (ticks every 1 second) */
	timer_loop(DEV_TIMER0, 1000000);
	schedule_next_task();
}

void handle_syscall(unsigned int syscall_id) {
	uart_print(DEV_UART0, "syscall(");
	uart_dprint(DEV_UART0, syscall_id);
	uart_print(DEV_UART0, ")!\n");
	switch (syscall_id) {
		case 0x0: /* yield */
			schedule_next_task();
		break;
		case 0x1: /* launch */
			launch_task((start_func_t*) cur_task->registers.r[0]);
		break;
		default:
			uart_print(DEV_UART0, "unknown syscall\n");
		break;
	}
}

void handle_interrupt(unsigned int interrupt_id) {
	uart_print(DEV_UART0, "interrupt(");
	uart_dprint(DEV_UART0, interrupt_id);
	uart_print(DEV_UART0, ")!\n");
	/* need to clear interrupt source if it is handled */
	switch (interrupt_id) {
		case 0x4:
			timer_clear(DEV_TIMER0);
			schedule_next_task();
		break;
		default:
			uart_print(DEV_UART0, "unknown interrupt\n");
		break;
	}
}

