#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>
#include <task.h>
#include <scheduler.h>

static task_t task1;
static task_t task2;

static void user1_f(void) {
	char a[] = {64, 0};
	while (1) {
		a[0]++;
		if (a[0] > 90) a[0] = 65;
		uart_print(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		for (int i = 0; i < 100000000; i++);
	}
}

static void user2_f(void) {
	unsigned int a = 0;
	while (1) {
		uart_dprint(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		a++;
		for (int i = 0; i < 20000000; i++);
	}
}

task_t* cur_task;

void init_scheduler(void) {
	init_task(&task1, &user1_f);
	init_task(&task2, &user2_f);
}

void schedule_next_task(void) {
	if (cur_task == &task1) {
		cur_task = &task2;
	} else {
		cur_task = &task1;
	}
}

