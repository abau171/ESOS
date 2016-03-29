#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <task.h>

extern task_t* cur_task;
extern unsigned int cur_tid;

void init_scheduler(void);

void schedule_next_task(void);

unsigned int scheduler_launch_task(start_func_t* start_func);

void run_queue_add_task(unsigned int tid);

unsigned int run_queue_read_task(void);

#endif

