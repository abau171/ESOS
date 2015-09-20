#include <scheduler.h>
#include <led.h>
#include <timerInterrupt.h>
#include <irqController.h>
#include <gpu_framebuffer.h>
#include <timer.h>

void startScheduler() {
	enableTimerInterrupt();
	enableInterrupts();
	setTimerInterruptDuration(10);
	while (1) {
	}
}

unsigned int x = 0;
unsigned int y = 0;
void schedulerTimerFinish() {
	setPixel(x, y, 0xffff);
	x++;
	if (x > getFrameBufferWidth()) {
		x = 0;
	}
	y++;
	if (y > getFrameBufferHeight()) {
		y = 0;
	}
	setTimerInterruptDuration(10000);
}

