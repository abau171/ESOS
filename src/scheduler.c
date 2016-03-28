#include <syscall.h>
#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>
#include <task.h>
#include <scheduler.h>

static task_t task1;
static task_t task2;

static void user1_f(void) {
	char a = 64;
	while (1) {
		a++;
		if (a > 90) a = 65;
		uart_cprint(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		for (int i = 0; i < 100000000; i++);
	}
}

static void user2_f(void) {
	unsigned int a = 0;
	while (1) {
		uart_xprint(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		a++;
		if (a % 8 == 0) yield();
		for (int i = 0; i < 20000000; i++);
	}
}

/* pointer to the next task that will be run */
task_t* cur_task;

void init_scheduler(void) {
	init_task(&task1, &user1_f);
	init_task(&task2, &user2_f);
}

void schedule_next_task(void) {
	/* choose the next task to be run */
	if (cur_task == &task1) {
		cur_task = &task2;
	} else {
		cur_task = &task1;
	}
}

