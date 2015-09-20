#define INTERRUPT_TIMER_DEVICE_ADDRESS 0x2000B400

#define ITIMER_32BIT (1 << 1)
#define ITIMER_PRESCALE_256 (2 << 2)
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
	interruptTimer->control =
		ITIMER_32BIT |
		ITIMER_ENABLE |
		ITIMER_INT_ENABLE | 
		ITIMER_PRESCALE_256;
}

void clearTimerInterrupt() {
	interruptTimer->irqClear = 1;
}
