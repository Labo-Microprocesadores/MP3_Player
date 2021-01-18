#include "arm_math.h"
#include "math.h"

#define SAMPLE_LENGTH       1024
#define NUMBER_OF_BANDS     8  
#define VUMETER_HEIGHT      8
#define NOISE               200
#define MAX_AMPLITUDE       1000


static  arm_rfft_fast_instance_f32 rfft_fast_instance;


void vumeterRefresh_init()
{
    arm_rfft_fast_init_f32(&rfft_fast_instance, SAMPLE_LENGTH);
}


int vumeterRefresh_fft(float32_t * inputSignal, float32_t sampleRate, float32_t *samples, float32_t lowerFreqBand, float32_t higherFreqBand)
{ 
    float32_t vumeterValues[NUMBER_OF_BANDS];
    int vumeterMatrix[NUMBER_OF_BANDS];
    float32_t nyquistFreq = sampleRate / 2;
    double binWidth = sampleRate / SAMPLE_LENGTH;
    unsigned int usableBins = roof(SAMPLE_LENGTH / 2 - 1);
    float32_t realHigherFreqBand = higherFreqBand  < nyquistFreq * 0.99 ? higherFreqBand :  nyquistFreq * 0.99; 
    float32_t freqMultiplierPerBand = pow((higherFreqBand / lowerFreqBand), (1 / (NUMBER_OF_BANDS - 1 )));

   
    float32_t output[SAMPLE_LENGTH / 2];
    float32_t outputFft[SAMPLE_LENGTH / 2];
    arm_rfft_fast_f32(&rfft_fast_instance, inputSignal, output, 0);
    /* Process the data through the Complex Magnitude Module for
    calculating the magnitude at each bin */
    arm_cmplx_mag_f32(outputFft, output, SAMPLE_LENGTH);

    //unsigned int binFreq[NUMBER_OF_BANDS];
    float32_t currentBinFreq;
    float32_t nextBinFreq;
    unsigned int currentCenterBin;
    unsigned int nextCenterBin;
    unsigned int lowerBin = 0;
    unsigned int higherBin;
    for (size_t i = 0; i < NUMBER_OF_BANDS; i++)
    {
        currentBinFreq = lowerFreqBand * pow(freqMultiplierPerBand, i);
        currentCenterBin = currentBinFreq / binWidth;
        lowerBin = i ? higherBin : 0;
        higherBin = (nextCenterBin-currentCenterBin)/2 + currentCenterBin;//calcular higherBin!!!
        
        for (size_t j = lowerBin; j < higherBin; j++)
        {
           if(outputFft[j] > NOISE)  
           {
            vumeterValues[i] += outputFft[j]; 
           }
        }
        int roundedHeight = floor(vumeterValues[i]/MAX_AMPLITUDE);
        vumeterMatrix[i] = roundedHeight > VUMETER_HEIGHT ? VUMETER_HEIGHT : roundedHeight;   
    } 
    //TODO

    //write_to_matrix(vumeterMatrix)
