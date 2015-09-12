#ifndef GPU_FRAMEBUFFER_H
#define GPU_FRAMEBUFFER_H

// initializes the frame buffer so a display can be used
// only a bit depth of 16 is currently supported
void initFrameBuffer(unsigned int width, unsigned int height, unsigned int bitDepth);

// sets a pixel on the display to a certain color
void setPixel(unsigned int x, unsigned int y, unsigned short color);

// sets a 4x4 block of pixels on the display to a certain color
// this simulates a much lower resolution display
void setPixel4x4(unsigned int x, unsigned int y, unsigned short color);

#endif