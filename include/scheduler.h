#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <task.h>

extern task_t* cur_task;
extern unsigned int cur_tid;

void init_scheduler(void);

void schedule_next_task(void);

#endif

