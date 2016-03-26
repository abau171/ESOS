#ifndef TIMER_H
#define TIME_H

#include <device_types.h>

void timer_loop(timer_address_t timer, unsigned int useconds);

void timer_clear(timer_address_t timer);

#endif

