#define SYSTEM_TIMER_ADDRESS ((volatile unsigned int*) 0x20003004)

unsigned int getSystemTime() {
	return *SYSTEM_TIMER_ADDRESS;
}

void spinMicro(unsigned int waitMicros) {
	unsigned int endTime = getSystemTime() + waitMicros;
	while (getSystemTime() < endTime);
}

void spinMilli(unsigned int waitMillis) {
	spinMicro(waitMillis * 1000);
}

void spinSecond(unsigned int waitSeconds) {
	spinMicro(waitSeconds * 1000000);
}