#ifndef TASK_H
#define TASK_H

#define TASK_STACK_SIZE 256

typedef struct {
	unsigned int r[17];
} register_snapshot_t;

typedef struct {
	register_snapshot_t registers;
	unsigned int stack[TASK_STACK_SIZE];
} task_t;

void init_task(task_t* task, void (*start_func)(void));

#endif

