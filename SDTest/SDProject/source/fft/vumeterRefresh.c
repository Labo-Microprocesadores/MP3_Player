#include "arm_math.h"
#include "math.h"
#include "matrix_display.h"
#include <stdbool.h>
#include "fsl_device_registers.h"
#include "vumeterRefresh.h"


#define SAMPLE_LENGTH       FFT_SIZE
#define NUMBER_OF_BANDS     8  
#define VUMETER_HEIGHT      8
#define NOISE               100
#define MAX_AMPLITUDE       60000
#define AVERAGE				2

static volatile arm_rfft_fast_instance_f32 rfft_fast_instance;
static volatile float32_t output[SAMPLE_LENGTH];
static volatile float32_t outputFft[SAMPLE_LENGTH / 2];
static volatile int vumeterMatrix[NUMBER_OF_BANDS];

float32_t fpowf(float32_t base, uint16_t n); //Fast exponenciation

void vumeterRefresh_init()
{
    arm_rfft_fast_init_f32(&rfft_fast_instance, SAMPLE_LENGTH);
}



int vumeterRefresh_fft(float32_t * inputSignal, float32_t sampleRate, int lowerFreqBand, int higherFreqBand)
{ 
    //float32_t vumeterValues[NUMBER_OF_BANDS];
    static char average = 0;
	unsigned int usableBins = (SAMPLE_LENGTH / 2 - 1);

    float32_t nyquistFreq = sampleRate / 2;
    double inv_binWidth = SAMPLE_LENGTH/sampleRate;
    double base = higherFreqBand / lowerFreqBand;
	double exp = 1.0f / (NUMBER_OF_BANDS - 1.0f );
	float32_t freqMultiplierPerBand = pow(base,exp);

    //float32_t realHigherFreqBand = higherFreqBand  < nyquistFreq * 0.99 ? higherFreqBand :  nyquistFreq * 0.99;
    //double base2 = 20000/80;
    //float32_t base3 = 20000/80;
    //int base4 = 20000/80;

   
    //GPIOC->PDOR |= (1 << 17);
    arm_rfft_fast_f32(&rfft_fast_instance, inputSignal, output, 0);
    /* Process the data through the Complex Magnitude Module for
    calculating the magnitude at each bin */
    for(uint16_t j = 0; j < SAMPLE_LENGTH/2; j++)
    {
    	float32_t temp = output[2*j]*output[2*j] + output[2*j+1]*output[2*j+1];
    	arm_sqrt_f32(temp, &outputFft[j]);
    }
    //arm_cmplx_mag_f32(output, outputFft, SAMPLE_LENGTH);
    outputFft[0] = 0; //Removing DC
    ///GPIOC->PDOR &= ~(1 << 17);

    //unsigned int binFreq[NUMBER_OF_BANDS];
    float32_t currentBinFreq = lowerFreqBand;
    float32_t nextBinFreq = lowerFreqBand * freqMultiplierPerBand;
    float32_t currentCenterBin;
    float32_t nextCenterBin;
    float32_t lowerBin = 0;
    float32_t higherBin;
    float32_t temp;
    for (size_t i = 0; i < NUMBER_OF_BANDS; i++)
    {
        //currentBinFreq = lowerFreqBand * fpowf(freqMultiplierPerBand, i);
        //nextBinFreq = lowerFreqBand * fpowf(freqMultiplierPerBand, i+1);

        currentCenterBin = currentBinFreq * inv_binWidth;
        nextCenterBin = nextBinFreq * inv_binWidth;
        lowerBin = i ? higherBin : 0;
        higherBin = (nextCenterBin-currentCenterBin)*0.5 + currentCenterBin;//calcular higherBin!!!

        temp = 0;
        for (size_t j = (int)(lowerBin); ((j < (int)(higherBin))&&(j < usableBins)); j++)
        {
        	temp += (outputFft[j] > NOISE)? outputFft[j] : 0;
        }
        int roundedHeight = (int)(temp/MAX_AMPLITUDE);
        //int roundedHeight = floor((vumeterValues[i]/(higherBin - lowerBin))/1000);
        vumeterMatrix[i] += (roundedHeight > VUMETER_HEIGHT ? VUMETER_HEIGHT : roundedHeight)/AVERAGE;

        currentBinFreq = nextBinFreq;
        nextBinFreq *= freqMultiplierPerBand;
    } 
    average = (average+1)%AVERAGE;
    if(average == 0)
    {
    	vumeterRefresh_write_to_matrix(vumeterMatrix);
    	for(int j = 0; j <  NUMBER_OF_BANDS; j++)
    		 vumeterMatrix[j] = 0;
    }
    return 0;//???
}
    //TODO


void vumeterRefresh_write_to_matrix(int * vumeterMatrix)
{

    /*pixel_t redPixel = {.R = 1, .G = 0, .B = 0};
    pixel_t yellowPixel = {.R = 1, .G = 1, .B = 0};
    pixel_t greenPixel = {.R = 0, .G = 1, .B = 0};
    pixel_t blackPixel = {.R = 0, .G = 0, .B = 0};
    */
	colors_t auxMatrix[VUMETER_HEIGHT * NUMBER_OF_BANDS];
    uint16_t size_m = VUMETER_HEIGHT * NUMBER_OF_BANDS;

    for(int i = VUMETER_HEIGHT-1 ; i >= 0 ; i--)
    {
        for(int j = 0 ; j < NUMBER_OF_BANDS ; j++)
        {
            if(vumeterMatrix[j] >= (VUMETER_HEIGHT - i))
            {
                if(i < (1 * VUMETER_HEIGHT / 8))
                    auxMatrix[size_m - VUMETER_HEIGHT * i - j] = RED;
                else if(i < (4 * VUMETER_HEIGHT / 8))
                    auxMatrix[size_m - VUMETER_HEIGHT * i - j] = YELLOW;
                else 
                    auxMatrix[size_m - VUMETER_HEIGHT * i - j] = GREEN;
            }
            else
                auxMatrix[size_m - VUMETER_HEIGHT * i - j] = CLEAN;
        }
    }
    md_writeBuffer(auxMatrix);
}


float32_t fpowf(float32_t base, uint16_t n)
{
	float ans = 1;
	while(n > 0)
	{
		if(n%2)
		{
			ans *= base;
		}
		n = n/2;
		base *= base;
	}
	return ans;
}
