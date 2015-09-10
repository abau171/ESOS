#ifndef GPIO_H
#define GPIO_H

#define GPIO_PIN_OFF 0
#define GPIO_PIN_ON 1

void setGPIOFunction(unsigned int pinNum, unsigned int functionNum);

void setGPIO(unsigned int pinNum, unsigned int pinVal);

#endif
