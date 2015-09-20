#include <timerInterrupt.h>

#define INTERRUPT_TIMER_DEVICE_ADDRESS 0x2000B400

#define ITIMER_32BIT (1 << 1)
#define ITIMER_PRESCALE_1 (0x00 << 2)
#define ITIMER_PRESCALE_16 (0x01 << 2)
#define ITIMER_PRESCALE_256 (0x10 << 2)
#define ITIMER_INT_ENABLE (1 << 5)
#define ITIMER_ENABLE (1 << 7)

struct InterruptTimer {
	volatile unsigned int load;
	volatile unsigned int value;
	volatile unsigned int control;
	volatile unsigned int irqClear;
	volatile unsigned int rawIRQ;
	volatile unsigned int maskedIRQ;
	volatile unsigned int reload;
	volatile unsigned int preDivider;
	volatile unsigned int freeRunningCounter;
};

static struct InterruptTimer* interruptTimer = (struct InterruptTimer*) INTERRUPT_TIMER_DEVICE_ADDRESS;

void setTimerInterruptDuration(unsigned int duration) {
	interruptTimer->load = duration;
	enableTimer();
}

void clearTimerInterrupt() {
	interruptTimer->irqClear = 1;
}

void enableTimer() {
	interruptTimer->control =
		ITIMER_32BIT |
		ITIMER_ENABLE |
		ITIMER_INT_ENABLE | 
		ITIMER_PRESCALE_1;
}

void disableTimer() {
	interruptTimer->control =
		ITIMER_32BIT |
		0 |
		ITIMER_INT_ENABLE | 
		ITIMER_PRESCALE_1;
}