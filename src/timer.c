#include <device_addresses.h>
#include <device_types.h>

#define TIMER_VALUE 0x1
#define TIMER_CONTROL 0x2
#define TIMER_INTCLR 0x3
#define TIMER_MIS 0x5

#define PIC ((volatile unsigned int*) 0x10140000)
#define PIC_TIMER01 0x10
#define VIC_INTENABLE 0x4

void timer_loop(timer_address_t timer, unsigned int useconds) {
	*(PIC + VIC_INTENABLE) = PIC_TIMER01;
	*timer = useconds;
	*(timer + 0x2) = 0x80 | 0x40 | 0x20 | 0x02;
}

void timer_clear(timer_address_t timer) {
	if (*(timer + TIMER_MIS)) {
		*(timer + TIMER_INTCLR) = 1;
	}
}

