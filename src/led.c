#include "led.h"
#include "timer.h"
#include "gpio.h"

void ledEnable() {
	setGPIOFunction(47, 1);
}

void ledOn() {
	setGPIO(47, GPIO_PIN_ON);
}

void ledOff() {
	setGPIO(47, GPIO_PIN_OFF);
}

void flashLED(unsigned int millis) {
	ledOn();
	spinMilli(millis);
	ledOff();
}

void flashWordLED(unsigned int word) {
	unsigned int mask = 0x80000000;
	do {
		if ((word & mask) > 0) {
			flashLED(1000);
		} else {
			flashLED(100);
		}
		spinMilli(500);
		mask >>= 1;
	} while (mask > 0);
}
