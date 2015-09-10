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
	spinMilli(100);
	ledOff();
}