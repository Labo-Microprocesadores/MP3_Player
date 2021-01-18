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

float32_t output[SAMPLE_LENGTH / 2];
float32_t outputFft[SAMPLE_LENGTH / 2];

int vumeterRefresh_fft(float32_t * inputSignal, float32_t sampleRate, int lowerFreqBand, int higherFreqBand)
{ 
    float32_t vumeterValues[NUMBER_OF_BANDS];
    int vumeterMatrix[NUMBER_OF_BANDS];
    float32_t nyquistFreq = sampleRate / 2;
    double binWidth = sampleRate / SAMPLE_LENGTH;
    unsigned int usableBins = ceil(SAMPLE_LENGTH / 2 - 1);
    float32_t realHigherFreqBand = higherFreqBand  < nyquistFreq * 0.99 ? higherFreqBand :  nyquistFreq * 0.99; 
    double base = higherFreqBand / lowerFreqBand;
    double exp = 1.0f / (NUMBER_OF_BANDS - 1.0f );
    double base2 = 20000/80;
    float32_t base3 = 20000/80;
    int base4 = 20000/80;
    float32_t freqMultiplierPerBand = pow(base,exp);

   

    arm_rfft_fast_f32(&rfft_fast_instance, inputSignal, output, 0);
    /* Process the data through the Complex Magnitude Module for
    calculating the magnitude at each bin */
    arm_cmplx_mag_f32(outputFft, output, SAMPLE_LENGTH);

    //unsigned int binFreq[NUMBER_OF_BANDS];
    float32_t currentBinFreq;
    float32_t nextBinFreq;
    float32_t currentCenterBin;
    float32_t nextCenterBin;
    float32_t lowerBin = 0;
    float32_t higherBin;
    for (size_t i = 0; i < NUMBER_OF_BANDS; i++)
    {
        currentBinFreq = lowerFreqBand * pow(freqMultiplierPerBand, i);
        nextBinFreq = lowerFreqBand * pow(freqMultiplierPerBand, i+1);
        currentCenterBin = currentBinFreq / binWidth;
        nextCenterBin = nextBinFreq / binWidth;
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
}
    //TODO

    //write_to_matrix(vumeterMatrix)
