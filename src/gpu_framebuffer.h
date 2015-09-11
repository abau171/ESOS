#ifndef GPU_FRAMEBUFFER_H
#define GPU_FRAMEBUFFER_H

void initFrameBuffer(unsigned int width, unsigned int height, unsigned int bitDepth);

void setPixel(unsigned int x, unsigned int y, unsigned short color);
void setPixel4x4(unsigned int x, unsigned int y, unsigned short color);

#endif