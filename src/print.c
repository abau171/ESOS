#include <print.h>
#include <gpu_framebuffer.h>

extern char font[];

void printChar(unsigned int x, unsigned int y, char c) {
	if (x >= getFrameBufferWidth() || y >= getFrameBufferHeight()) {
		return;
	}
	c -= 32;
	for (int subx = 0; subx < 6; subx++) {
		for (int suby = 0; suby < 6; suby++) {
			char row = font[6 * c + suby];
			char mask = 0x80 >> subx;
			if (row & mask) {
				setPixel(6 * x + subx, 6 * y + suby, 0xffff);
			} else {
				setPixel(6 * x + subx, 6 * y + suby, 0x0000);
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

void printUInt(unsigned int x, unsigned int y, unsigned int i) {
	unsigned int place = 0;
	unsigned long j = i;
	while (j > 9) {
		j -= j % 10;
		j /= 10;
		place++;
	}
	do {
		unsigned int ones = i % 10;
		char onesChar = ones + 48;
		printChar(x + place, y, onesChar);
		i -= ones;
		i /= 10;
		place--;
	} while (i > 0);
}

void printInt(unsigned int x, unsigned int y, int i) {
	unsigned int isNegative = i < 0;
	if (isNegative) {
		printChar(x, y, '-');
		printUInt(x + 1, y, -i);
	} else {
		printUInt(x, y, i);
	}
}
