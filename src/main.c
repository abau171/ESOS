#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>
#include <timer.h>
#include <task.h>

task_t task1;
task_t task2;

void user1_f() {
	uart_print(DEV_UART0, "user 1\n");
	timer_usleep(DEV_TIMER0, 1000000);
	uart_print(DEV_UART0, "user done, resetting...\n");
	svc();
}

void user2_f() {
	uart_print(DEV_UART0, "user 2\n");
	timer_usleep(DEV_TIMER0, 1000000);
	uart_print(DEV_UART0, "user done, resetting...\n");
	svc();
}

void main() {
	uart_print(DEV_UART0, "ESOS reboot\n");
	init_task(&task1, &user1_f);
	init_task(&task2, &user2_f);
	while (1) {
		activate(&task1);
		activate(&task2);
	}
}

