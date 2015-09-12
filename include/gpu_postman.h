#ifndef GPU_POSTMAN_H
#define GPU_POSTMAN_H

// writes a message to the gpu on a specified channel
void gpuWrite(unsigned int channel, unsigned int message);

// reads a message from the gpu, ignoring all messages until one
// belonging to the desired channel is found
unsigned int gpuRead(unsigned int channel);

#endif