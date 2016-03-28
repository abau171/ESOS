#ifndef TASK_H
#define TASK_H

#define NUM_TASKS 100
#define TASK_STACK_SIZE 256

#define TASK_DEAD 0
#define TASK_ALIVE 1

typedef struct {
	unsigned int r[17];
} register_snapshot_t;

typedef struct {
	register_snapshot_t registers;
	unsigned int state;
	unsigned int stack[TASK_STACK_SIZE];
} task_t;

extern task_t tasks[NUM_TASKS];

void init_task(void);

unsigned int launch_task(void (*start_func)(void));

#endif

