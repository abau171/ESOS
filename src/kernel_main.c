#include "gpio.h"
#include "timer.h"
#include "led.h"
#include "gpu_framebuffer.h"

void kernel_main() {
	initFrameBuffer(1920, 1080, 16);
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
