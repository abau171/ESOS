#ifndef LED_H
#define LED_H

// enables the use of the LED
void ledEnable();

// turns the LED on
void ledOn();

// turns the LED off
void ledOff();

// flashes the LED for a number of milliseconds
void flashLED(unsigned int millis);

// flashes the LED in the sequence of the bits of a word
void flashWordLED(unsigned int word);

#endif
