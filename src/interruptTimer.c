#define INTERRUPT_CONTROLLER_ADDRESS 0x2000B200

#define TIMER_IRQ_BIT 1

struct IRQController {
	volatile unsigned int basicPending;
	volatile unsigned int irq1Pending;
	volatile unsigned int irq2Pending;
	volatile unsigned int fiqControl;
	volatile unsigned int irq1Enable;
	volatile unsigned int irq2Enable;
	volatile unsigned int basicEnable;
	volatile unsigned int irq1Disable;
	volatile unsigned int irq2Disable;
	volatile unsigned int basicDisable;
};

static struct IRQController* irqController = (struct IRQController*) INTERRUPT_CONTROLLER_ADDRESS;

void enableInterruptTimer() {
	irqController->basicEnable = TIMER_IRQ_BIT;
}



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

void setTimerDuration(unsigned int duration) {
	interruptTimer->load = duration;
	interruptTimer->control =
		ITIMER_32BIT |
		ITIMER_ENABLE |
		ITIMER_INT_ENABLE | 
		ITIMER_PRESCALE_256;
}

void clearInterrupt() {
	interruptTimer->irqClear = 1;
}
