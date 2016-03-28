#include <syscall.h>
#include <context_switch.h>
#include <device_addresses.h>
#include <uart.h>
#include <task.h>
#include <scheduler.h>

static void user2_f(void);

static void user1_f(void) {
	char a = 64;
	while (1) {
		a++;
		if (a > 90) {
			a = 65;
			unsigned int launched_tid = launch(&user2_f);
			uart_print(DEV_UART0, "f1 launched tid ");
			uart_dprint(DEV_UART0, launched_tid);
			uart_cprint(DEV_UART0, '\n');
		}
		uart_cprint(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		for (int i = 0; i < 100000000; i++);
	}
}

static void user2_f(void) {
	unsigned int tid = get_tid();
	uart_print(DEV_UART0, "f2 tid ");
	uart_dprint(DEV_UART0, tid);
	uart_cprint(DEV_UART0, '\n');
	unsigned int a = 0;
	while (1) {
		uart_xprint(DEV_UART0, a);
		uart_cprint(DEV_UART0, '\n');
		a++;
		for (int i = 0; i < 200000000; i++);
	}
}

/* pointer to the next task that will be run */
task_t* cur_task;

unsigned int cur_tid = 0;

void init_scheduler(void) {
	launch_task(&user1_f);
}

void schedule_next_task(void) {
	/* choose the next task to be run */
	do {
		cur_tid = (cur_tid + 1) % NUM_TASKS;
	} while (tasks[cur_tid].state != TASK_ALIVE);
	cur_task = &tasks[cur_tid];
}

