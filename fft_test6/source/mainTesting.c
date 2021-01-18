
#include "arm_math.h"
#include "arm_const_structs.h"
#include "vumeterRefresh.h"


int main (void)
{
	vumeterRefresh_init();

	  float32_t baja[1024];
	  float32_t alta[1024];
	  float32_t otra[1024];
	  float32_t otra2[1024];
	  float32_t otra3[1024];
	  float32_t otra4[1024];
	  float32_t signal[1024];
	  int i;
	  for(i=0; i<1024; i++){
	         baja[i] = 1.2f*arm_sin_f32(2*3.1415926f*50*i/44100);
	         alta[i] = 10.0f*arm_sin_f32(2*3.1415926f*10*i/44100);
	         otra[i] = 20.0f*arm_sin_f32(2*3.1415926f*100*i/44100);
	         otra2[i] = 30.0f*arm_sin_f32(2*3.1415926f*200*i/44100);
	         otra3[i] = 30.0f*arm_sin_f32(2*3.1415926f*300*i/44100);
	         otra4[i] = 30.0f*arm_sin_f32(2*3.1415926f*500*i/44100);
	         signal[i] = baja[i]+alta[i]+otra[i]+otra2[i]+otra3[i]+otra4[i];
	     }
	vumeterRefresh_fft(signal, 44100, 80, 20000);
	return 0;
}
