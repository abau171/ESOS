#ifndef SYSCALL_H
#define SYSCALL_H

#include <task.h>

void yield();

unsigned int launch(start_func_t* start_func);

unsigned int get_tid();

#endif

