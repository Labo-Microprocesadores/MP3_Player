#ifndef _VUMETER_REFRESH_H
#define _VUMETER_REFRESH_H
#include<stdio.h>
#include<stdint.h>

void vumeterRefresh_init();
int vumeterRefresh_fft(int sample_rate, float32_t *samples, unsigned int sampleLength, unsigned int lowerFreqBand,unsigned int higherFreqBand);
#endif //_VUMETER_REFRESH_H

/**
 *
 * End of file.
 */