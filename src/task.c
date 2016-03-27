#include <task.h>

#define TASK_STACK_SIZE 256

void init_task(task_t* task, void (*start_func)(void)) {
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
}

