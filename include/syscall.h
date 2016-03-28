#ifndef SYSCALL_H
#define SYSCALL_H

#include <task.h>

void yield();

void launch(start_func_t* start_func);

#endif

