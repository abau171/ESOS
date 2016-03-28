#ifndef SYSCALL_H
#define SYSCALL_H

void yield();

void launch(void (*start_func)(void));

#endif

