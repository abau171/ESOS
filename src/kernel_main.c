#include "gpio.h"
#include "timer.h"

void kernel_main() {
	setGPIOFunction(47, 1);
	spinSecond(3);
	setGPIO(47, GPIO_PIN_ON);
}
