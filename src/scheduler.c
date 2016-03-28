#include <syscall.h>
#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>
#include <task.h>
#include <scheduler.h>

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
		for (int i = 0; i < 20000000; i++);
	}
}

/* pointer to the next task that will be run */
task_t* cur_task;

unsigned int cur_tid = 0;

void init_scheduler(void) {
	launch_task(&user1_f);
	launch_task(&user2_f);
	launch_task(&user2_f);
}

void schedule_next_task(void) {
	/* choose the next task to be run */
	do {
		cur_tid = (cur_tid + 1) % NUM_TASKS;
	} while (tasks[cur_tid].state != TASK_ALIVE);
	cur_task = &tasks[cur_tid];
}

