#include "gpu_framebuffer.h"

struct Character {
	char row[8];
};

struct Character char_A = {
	.row = {0x10, 0x10, 0x28, 0x28, 0x44, 0x7c, 0x82, 0x82}
};

struct Character char_B = {
	.row = {0xf8, 0x84, 0x84, 0xf8, 0x84, 0x82, 0x82, 0xfc}
};

struct Character char_qMark = {
	.row = {0x3c, 0x42, 0x42, 0x0c, 0x10, 0x10, 0x00, 0x10}
};

void printChar(unsigned int x, unsigned int y, char c) {
	struct Character* chosenChar;
	if (c == 'A') {
		chosenChar = &char_A;
	} else if (c == 'B') {
		chosenChar = &char_B;
	} else {
		chosenChar = &char_qMark;
	}
	for (int subx = 0; subx < 8; subx++) {
		for (int suby = 0; suby < 8; suby++) {
			char row = chosenChar->row[suby];
			char mask = 0x80 >> subx;
			if (row & mask) {
				setPixel4x4(8 * x + subx, 8 * y + suby, 0xffff);
			}
		}
	}
}