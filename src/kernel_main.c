#include "gpio.h"
#include "timer.h"
#include "led.h"

void kernel_main() {
}

void kernel_hangLoop() {
	ledEnable();
	while (1) {
		flashLED(50);
		spinMilli(100);
		flashLED(50);
		spinMilli(800);
	}
}
