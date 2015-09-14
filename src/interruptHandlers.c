#include <interruptVectorTable.h>
#include <led.h>
#include <interruptTimer.h>

void undefinedInstructionHandler() {

}

void softwareInterruptHandler() {

}

void prefetchAbortHandler() {

}

void dataAbortHandler() {

}

static unsigned int i = 0;
void interruptHandler() {
	if (i) {
		i = 0;
		ledOn();
	} else {
		i = 1;
		ledOff();
	}
	clearInterrupt();
}

void fastInterruptHandler() {

}
