#include <device_addresses.h>
#include <uart.h>
#include <task.h>

static unsigned int next_task_id = 0;
task_t tasks[NUM_TASKS];

void init_task(void) {
	for (int i = 0; i < NUM_TASKS; i++) {
		tasks[i].state = TASK_DEAD;
	}
}

unsigned int launch_task(start_func_t* start_func) {
	/* grab current task id, increment next task id */
	unsigned int tid = next_task_id;
	next_task_id++;
	/* find task */
	task_t* task = &tasks[tid];
	/* initialize all registers to zero */
	for (unsigned int i = 0; i < 17; i++) {
		task->registers.r[i] = 0;
	}
	/* set sp to task's stack */
	task->registers.r[13] = (unsigned int) &(task->stack[TASK_STACK_SIZE]);
	/* set pc to start function */
	task->registers.r[15] = (unsigned int) start_func;
	/* set cpsr to user mode with no flags set */
	task->registers.r[16] = 0x10;
	/* set task state to alive */
	task->state = TASK_ALIVE;
	/* return tid */
	return tid;
}

