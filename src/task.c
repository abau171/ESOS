#include <task.h>

#define NUM_TASKS 10
#define TASK_STACK_SIZE 256

void init_task(task_t* task, void (*start_func)(void)) {
	for (unsigned int i = 0; i < 17; i++) {
		task->registers.r[i] = 0;
	}
	task->registers.r[13] = (unsigned int) &(task->stack[TASK_STACK_SIZE]);
	task->registers.r[15] = (unsigned int) start_func;
	task->registers.r[16] = 0x10;
}

