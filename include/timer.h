#ifndef TIMER_H
#define TIMER_H

// gets the current system time in microseconds
unsigned long getSystemTime();

// spins the cpu for some number of microseconds
void spinMicro(unsigned int waitMicros);

// spins the cpu for some number of milliseconds
void spinMilli(unsigned int waitMillis);

// spins the cpu for some number of seconds
void spinSecond(unsigned int waitSeconds);

#endif
