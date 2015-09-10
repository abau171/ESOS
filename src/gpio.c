#include "gpio.h"

#define GPIO_ADDRESS ((unsigned int*) 0x20200000)

#define MAX_PIN_NUM 53
#define MAX_FCN_NUM 7

#define WORD1_MAX_PIN_NUM 31

#define MAX_PIN_VAL 1

void setGPIOFunction(unsigned int pinNum, unsigned int functionNum) {
	if (pinNum > MAX_PIN_NUM || functionNum > MAX_FCN_NUM) {
		return;
	}

	int ones = pinNum % 10;
	int tens = (pinNum - ones) / 10;

	unsigned int shiftedFunctionNum = functionNum << (3 * ones);
	unsigned int* pinAddress = GPIO_ADDRESS + tens;

	*pinAddress = shiftedFunctionNum;
	return;
}

void setGPIO(unsigned int pinNum, unsigned int pinVal) {
	if (pinNum > MAX_PIN_NUM || pinVal > MAX_PIN_VAL) {
		return;
	}

	unsigned int* pinAddress = GPIO_ADDRESS;
	if (pinVal == GPIO_PIN_ON) {
		pinAddress += 7;
	} else {
		pinAddress += 10;
	}

	unsigned int wordPinNum = pinNum;
	if (pinNum > WORD1_MAX_PIN_NUM) {
		pinAddress += 1;
		wordPinNum -= 32;
	}

	int setWord = 1 << wordPinNum;
	*pinAddress = setWord;
}
