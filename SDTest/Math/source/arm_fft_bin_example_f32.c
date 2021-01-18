/* ----------------------------------------------------------------------
* Copyright (C) 2010-2012 ARM Limited. All rights reserved.
*
* $Date:         17. January 2013
* $Revision:     V1.4.0
*
* Project:       CMSIS DSP Library
* Title:	     arm_fft_bin_example_f32.c
*
* Description:   Example code demonstrating calculation of Max energy bin of
*                frequency domain of input signal.
*
* Target Processor: Cortex-M4/Cortex-M3
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ARM LIMITED nor the names of its contributors
*     may be used to endorse or promote products derived from this
*     software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
 * -------------------------------------------------------------------- */

/**
 * @ingroup groupExamples
 */

/**
 * @defgroup FrequencyBin Frequency Bin Example
 *
 * \par Description
 * \par
 * Demonstrates the calculation of the maximum energy bin in the frequency
 * domain of the input signal with the use of Complex FFT, Complex
 * Magnitude, and Maximum functions.
 *
 * \par Algorithm:
 * \par
 * The input test signal contains a 10 kHz signal with uniformly distributed white noise.
 * Calculating the FFT of the input signal will give us the maximum energy of the
 * bin corresponding to the input frequency of 10 kHz.
 *
 * \par Block Diagram:
 * \image html FFTBin.gif "Block Diagram"
 * \par
 * The figure below shows the time domain signal of 10 kHz signal with
 * uniformly distributed white noise, and the next figure shows the input
 * in the frequency domain. The bin with maximum energy corresponds to 10 kHz signal.
 * \par
 * \image html FFTBinInput.gif "Input signal in Time domain"
 * \image html FFTBinOutput.gif "Input signal in Frequency domain"
 *
 * \par Variables Description:
 * \par
 * \li \c testInput_f32_10khz points to the input data
 * \li \c testOutput points to the output data
 * \li \c fftSize length of FFT
 * \li \c ifftFlag flag for the selection of CFFT/CIFFT
 * \li \c doBitReverse Flag for selection of normal order or bit reversed order
 * \li \c refIndex reference index value at which maximum energy of bin ocuurs
 * \li \c testIndex calculated index value at which maximum energy of bin ocuurs
 *
 * \par CMSIS DSP Software Library Functions Used:
 * \par
 * - arm_cfft_f32()
 * - arm_cmplx_mag_f32()
 * - arm_max_f32()
 *
 * <b> Refer  </b>
 * \link arm_fft_bin_example_f32.c \endlink
 *
 */


/** \example arm_fft_bin_example_f32.c
  */


#include "arm_math.h"
#include "arm_const_structs.h"

#define TEST_LENGTH_SAMPLES 2048

/* -------------------------------------------------------------------
* External Input and Output buffer Declarations for FFT Bin Example
* ------------------------------------------------------------------- */
extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
static float32_t testOutput2[TEST_LENGTH_SAMPLES/2];
static float32_t testOutput[512];

float32_t new_input[1024];
float32_t new_output[1024];

/* ------------------------------------------------------------------
* Global variables for FFT Bin Example
* ------------------------------------------------------------------- */
uint32_t fftSize = 1024;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 0;

/* Reference index at which max energy of bin ocuurs */
uint32_t refIndex = 213, testIndex = 0;

/* ----------------------------------------------------------------------
* Max magnitude FFT Bin test
* ------------------------------------------------------------------- */
arm_rfft_fast_instance_f32 rfft_fast_instance;

int32_t main(void)
{

  arm_status status;
  float32_t maxValue;

  status = ARM_MATH_SUCCESS;

  /* Process the data through the CFFT/CIFFT module */
 //arm_cfft_f32(&arm_cfft_sR_f32_len1024, testInput_f32_10khz, ifftFlag, doBitReverse);
 //arm_cmplx_mag_f32(testInput_f32_10khz, testOutput2, fftSize);

  uint16_t fftLen = 1024;

  float32_t baja[1024];
  float32_t alta[1024];
  float32_t otra[1024];
  float32_t otra2[1024];
  float32_t otra3[1024];
  float32_t otra4[1024];
  float32_t signal[1024];
  int i;
  for(i=0; i<1024; i++){
         baja[i] = 1.2f*arm_sin_f32(2*3.1415926f*50*i/1024);
         alta[i] = 10.0f*arm_sin_f32(2*3.1415926f*10*i/1024);
         otra[i] = 20.0f*arm_sin_f32(2*3.1415926f*100*i/1024);
         otra2[i] = 30.0f*arm_sin_f32(2*3.1415926f*200*i/1024);
         otra3[i] = 30.0f*arm_sin_f32(2*3.1415926f*300*i/1024);
         otra4[i] = 30.0f*arm_sin_f32(2*3.1415926f*500*i/1024);
         signal[i] = baja[i]+alta[i]+otra[i]+otra2[i]+otra3[i]+otra4[i];
     }

  //int i;
  for(i=0;i<1024;i++)
  {
	  new_input[i] = testInput_f32_10khz[2*i];
  }

  arm_rfft_fast_init_f32(&rfft_fast_instance, fftLen);
  //arm_rfft_fast_f32(&rfft_fast_instance, new_input, new_output, ifftFlag);
  arm_rfft_fast_f32(&rfft_fast_instance, signal, new_output, ifftFlag);


  /* Process the data through the Complex Magnitude Module for
  calculating the magnitude at each bin */
  //arm_cmplx_mag_f32(testInput_f32_10khz, testOutput, fftSize);
  arm_cmplx_mag_f32(new_output, testOutput, fftSize);



  /* Calculates maxValue and returns corresponding BIN value */
  arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);

  if (testIndex !=  refIndex)
  {
    status = ARM_MATH_TEST_FAILURE;
  }

  /* ----------------------------------------------------------------------
  ** Loop here if the signals fail the PASS check.
  ** This denotes a test failure
  ** ------------------------------------------------------------------- */

  if ( status != ARM_MATH_SUCCESS)
  {
    while (1);
  }

  while (1);                             /* main function does not return */
}

 /** \endlink */
