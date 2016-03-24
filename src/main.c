#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>
#include <timer.h>
#include <task.h>

task_t task1;
task_t task2;

void user1_f() {
	char a[] = {64, 0};
	while (1) {
		a[0]++;
		if (a[0] > 90) a[0] = 65;
		uart_print(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		timer_usleep(DEV_TIMER0, 100000);
		svc();
	}
}

unsigned int u2_rec(unsigned int a) {
	if (a == 0) return a + 1;
	else return u2_rec(a - 1) + 1;
}

void user2_f() {
	unsigned int a = 0;
	while (1) {
		uart_dprint(DEV_UART0, u2_rec(a));
		uart_cprint(DEV_UART0, '\n');
		a++;
		timer_usleep(DEV_TIMER0, 1000000);
		svc();
	}
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

