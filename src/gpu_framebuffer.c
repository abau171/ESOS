#include <gpu_framebuffer.h>
#include <gpu_postman.h>
#include <led.h>

#define TO_GPU_ADDRESS_OFFSET ((unsigned int) 0x40000000)

struct FrameBufferInfo {
	unsigned int physicalWidth;
	unsigned int physicalHeight;
	unsigned int virtualWidth;
	unsigned int virtualHeight;
	unsigned int pitch;
	unsigned int bitDepth;
	unsigned int x;
	unsigned int y;
	unsigned int gpuPointer;
	unsigned int size;
};

volatile __attribute__((aligned (16))) struct FrameBufferInfo frameBufferInfo;

void initFrameBuffer(unsigned int width, unsigned int height, unsigned int bitDepth) {
	// TODO validate input
	frameBufferInfo.physicalWidth = width;
	frameBufferInfo.physicalHeight = height;
	frameBufferInfo.virtualWidth = width;
	frameBufferInfo.virtualHeight = height;
	frameBufferInfo.bitDepth = bitDepth;
	gpuWrite(1, ((unsigned int) &frameBufferInfo) + TO_GPU_ADDRESS_OFFSET);
	unsigned int result = gpuRead(1);
	// nothing done with result yet, but if it is not 0 then an error has occurred
}

unsigned int getFrameBufferWidth() {
	return frameBufferInfo.virtualWidth;
}

unsigned int getFrameBufferHeight() {
	return frameBufferInfo.virtualHeight;
}

void setPixel(unsigned int x, unsigned int y, unsigned short color) {
	if (x >= getFrameBufferWidth() || y >= getFrameBufferHeight()) {
		return;
	}
	unsigned int offset = 2 * (y * frameBufferInfo.virtualWidth + x);
	*((unsigned short*) (frameBufferInfo.gpuPointer + offset)) = color;
}
