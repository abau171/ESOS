#include "gpio.h"

void kernel_main() {
	setGPIOFunction(47, 1);
	setGPIO(47, GPIO_PIN_ON);
}
