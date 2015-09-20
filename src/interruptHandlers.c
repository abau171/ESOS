#include <interruptHandlers.h>
#include <led.h>
#include <timerInterrupt.h>
#include <gpu_framebuffer.h>
#include <scheduler.h>

void undefinedInstructionHandler() {

}

void softwareInterruptHandler() {

}

void prefetchAbortHandler() {

}

void dataAbortHandler() {

}

void interruptHandler() {
	disableTimer();
	clearTimerInterrupt();
	schedulerTimerFinish();
}

void fastInterruptHandler() {

}
