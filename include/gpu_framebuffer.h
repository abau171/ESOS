#ifndef GPU_FRAMEBUFFER_H
#define GPU_FRAMEBUFFER_H

// initializes the frame buffer so a display can be used
// only a bit depth of 16 is currently supported
void initFrameBuffer(unsigned int width, unsigned int height, unsigned int bitDepth);

// gets the width of the frame buffer in pixels
unsigned int getFrameBufferWidth();

// gets the height of the frame buffer in pixels
unsigned int getFrameBufferHeight();

// sets a pixel on the display to a certain color
void setPixel(unsigned int x, unsigned int y, unsigned short color);

#endif