#include "gpio.h"
#include "timer.h"

void kernel_main() {
}

void flashLED(unsigned int millis) {
	setGPIO(47, GPIO_PIN_ON);
	spinMilli(100);
	setGPIO(47, GPIO_PIN_OFF);
}

void kernel_hangLoop() {
	setGPIOFunction(47, 1);
	while (1) {
		flashLED(100);
		spinMilli(100);
		flashLED(100);
		spinMilli(700);
	}
}