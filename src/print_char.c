#include "print_char.h"
#include "gpu_framebuffer.h"

extern char font[];

void printChar(unsigned int x, unsigned int y, char c) {
	c -= 65;
	for (int subx = 0; subx < 8; subx++) {
		for (int suby = 0; suby < 6; suby++) {
			char row = font[6 * c + suby];
			char mask = 0x80 >> subx;
			if (row & mask) {
				setPixel(8 * x + subx, 8 * y + suby, 0xffff);
			}
		}
	}
}

void printStr(unsigned int x, unsigned int y, char* str) {
	unsigned int i = 0;
	while (str[i] != 0) {
		char c = str[i];
		printChar(x + i, y, c);
		i++;
	}
}
