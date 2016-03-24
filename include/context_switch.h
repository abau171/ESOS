#ifndef CONTEXT_SWITCH_H
#define CONTEXT_SWITCH_H

#include <task.h>

void activate(task_t* stack);

void svc();

#endif

