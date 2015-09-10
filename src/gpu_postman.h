#ifndef GPU_POSTMAN_H
#define GPU_POSTMAN_H

void gpuWrite(unsigned int channel, unsigned int message);

unsigned int gpuRead(unsigned int channel);

#endif