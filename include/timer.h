#ifndef TIMER_H
#define TIMER_H

// microseconds
unsigned int getSystemTime();

void spinMicro(unsigned int waitMicros);

void spinMilli(unsigned int waitMillis);

void spin(unsigned int waitSeconds);

#endif
