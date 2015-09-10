#ifndef TIMER_H
#define TIMER_H

unsigned long getSystemTime();

void spinMicro(unsigned int waitMicros);

void spinMilli(unsigned int waitMillis);

void spinSecond(unsigned int waitSeconds);

#endif
