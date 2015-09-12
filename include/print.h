#ifndef PRINT_H
#define PRINT_H

// prints a character to a position in the terminal
void printChar(unsigned int x, unsigned int y, char c);

// prints a string to the terminal
void printStr(unsigned int x, unsigned int y, char* str);

// prints an unsigned integer to the terminal
void printUInt(unsigned int x, unsigned int y, unsigned int i);

// prints a signed integer to the terminal
void printInt(unsigned int x, unsigned int y, int i);

#endif