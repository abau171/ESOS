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

void enableTimerInterrupt() {
	irqController->basicEnable = TIMER_IRQ_BIT;
}

void disableTimerInterrupt() {
	irqController->basicDisable = TIMER_IRQ_BIT;
}
