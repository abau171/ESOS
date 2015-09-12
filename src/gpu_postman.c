#include <gpu_postman.h>
#include <led.h>

#define GPU_MAILBOX_DEVICE_ADDRESS ((struct GPUMailbox*) 0x2000B880)

#define MAX_CHANNEL 7

struct GPUMailbox {
	unsigned int read;
	unsigned int padding[3];
	unsigned int poll;
	unsigned int sender;
	unsigned int status;
	unsigned int config;
	unsigned int write;
};

volatile struct GPUMailbox* gpuMailbox = GPU_MAILBOX_DEVICE_ADDRESS;

void gpuWrite(unsigned int channel, unsigned int message) {
	if (channel > MAX_CHANNEL || channel == 0) {
		return;
	}
	if ((message & 0xf) != 0) {
		return;
	}
	unsigned int writeWord = channel | message;
	while (gpuMailbox->status & 0x80000000);
	gpuMailbox->write = writeWord;
}

unsigned int gpuRead(unsigned int channel) {
	if (channel > MAX_CHANNEL || channel == 0) {
		return 0;
	}
	unsigned int readWord;
	do {
		while (gpuMailbox->status & 0x40000000);
		readWord = gpuMailbox->read;
	} while ((readWord & 0xf) != channel);
	return (readWord & 0xfffffff0);
}
