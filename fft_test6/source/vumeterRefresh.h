#ifndef _VUMETER_REFRESH_H
#define _VUMETER_REFRESH_H
#include<stdio.h>
#include<stdint.h>

void vumeterRefresh_init();
int vumeterRefresh_fft(float32_t * inputSignal, float32_t sampleRate, int lowerFreqBand, int higherFreqBand);

#endif
/**
 *
 * End of file.
 */
