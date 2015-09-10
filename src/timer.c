#define TIMER_DEVICE_ADDRESS ((struct TimerDevice*) 0x20003000)

struct TimerDevice {
	unsigned int status;
	unsigned int counterLow;
	unsigned int counterHigh;
	unsigned int compare[4];
};

volatile struct TimerDevice* timerDevice = TIMER_DEVICE_ADDRESS;

unsigned int getSystemTime() {
	return timerDevice->counterLow;
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
