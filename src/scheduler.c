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

/* tid of active thread */
unsigned int cur_tid = 0;

/* run queue : ring buffer of tids */
unsigned int run_queue[NUM_TASKS];
unsigned int run_queue_start_index = 0;
unsigned int run_queue_end_index = 0;

/* whether last task was the idle task */
unsigned int cur_task_idle = 1;

void init_scheduler(void) {
	scheduler_launch_task(&user1_f);
}

void schedule_next_task(void) {
	/* choose the next task to be run */
	if (!cur_task_idle) {
		run_queue_add_task(cur_tid);
	}
	if (run_queue_start_index != run_queue_end_index) {
		cur_tid = run_queue_read_task();
		cur_task = &tasks[cur_tid];
		cur_task_idle = 0;
	} else {
		// cur_task = /* idle task */
		cur_task_idle = 1;
	}
}

unsigned int scheduler_launch_task(start_func_t* start_func) {
	unsigned int tid = launch_task(start_func);
	run_queue_add_task(tid);
}

void run_queue_add_task(unsigned int tid) {
	run_queue[run_queue_end_index] = tid;
	run_queue_end_index = (run_queue_end_index + 1) % NUM_TASKS;
}

unsigned int run_queue_read_task() {
	unsigned int tid = run_queue[run_queue_start_index];
	run_queue_start_index = (run_queue_start_index + 1) % NUM_TASKS;
	return tid;
}

