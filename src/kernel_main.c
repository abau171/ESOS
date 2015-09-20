#include <timer.h>
#include <led.h>
#include <gpu_framebuffer.h>
#include <print.h>
#include <scheduler.h>

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 270
#define DISPLAY_BIT_DEPTH 16

void kernel_main() {
	initFrameBuffer(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_BIT_DEPTH);
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
