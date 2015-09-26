#include <timer.h>
#include <led.h>
#include <scheduler.h>

void kernel_main() {
	startScheduler();
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
