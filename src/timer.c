#include <device_types.h>

void timer_usleep(timer_address_t addr, unsigned int useconds) {
	volatile unsigned int* timer = (unsigned int*) 0x101e2000;
	*timer = useconds;
	*(timer + 0x2) = 0x80 | 0x01 | 0x02;
	while (*(timer + 0x1) > 0);
}

