#ifndef GPIO_H
#define GPIO_H

#define GPIO_PIN_OFF 0
#define GPIO_PIN_ON 1

// sets the gpio function of a gpio pin
void setGPIOFunction(unsigned int pinNum, unsigned int functionNum);

// sets the state of a gpio pin
void setGPIO(unsigned int pinNum, unsigned int pinVal);

#endif
