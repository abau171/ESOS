#include "gpio.h"
#include "timer.h"
#include "led.h"
#include "gpu_framebuffer.h"

void kernel_main() {
	unsigned int width = 1920;
	unsigned int height = 1080;
	initFrameBuffer(width, height, 16);

	unsigned int vwidth = width / 4;
	unsigned int vheight = height / 4;
	for (int y = 0; y < vheight; y++) {
		for (int x = 0; x < vwidth; x++) {
			if ((x + y) % 2 == 0) {
				setPixel4x4(x, y, 0xffff);
			}
		}
	}
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
