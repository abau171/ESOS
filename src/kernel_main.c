#include <timer.h>
#include <led.h>
#include <gpu_framebuffer.h>
#include <print.h>

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 270
#define DISPLAY_BIT_DEPTH 16

void kernel_main() {
	initFrameBuffer(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_BIT_DEPTH);
	printStr(0, 0, "ESOS");
	printStr(0, 1, "EVENTUALLY SENTIENT OPERATING SYSTEM");
	printStr(0, 3, " !\"#$%&'()*+,-./");
	printStr(0, 4, "0123456789");
	printStr(0, 5, ":;<=>?@");
	printStr(0, 6, "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	printStr(0, 7, "[\\]^_`");
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
