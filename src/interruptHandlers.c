#include <interruptVectorTable.h>
#include <led.h>
#include <interruptTimer.h>
#include <gpu_framebuffer.h>

void undefinedInstructionHandler() {

}

void softwareInterruptHandler() {

}

void prefetchAbortHandler() {

}

void dataAbortHandler() {

}

static unsigned int color = 0;
static unsigned int x = 0;
static unsigned int y = 0;
void interruptHandler() {
	x++;
	unsigned int fbHeight = getFrameBufferHeight();
	if (x >= fbHeight) {
		x = 0;
		y++;
	}
	unsigned int fbWidth = getFrameBufferWidth();
	if (y >= fbWidth) {
		y = 0;
	}
	color++;
	setPixel(x, y, color);
	clearInterrupt();
}

void fastInterruptHandler() {

}