

#include "AudioPlayer.h"
#include "fsl_debug_console.h"
#include "math.h"

//extern uint16_t song;




uint16_t g_dacDataArray[AUDIO_PLAYER_BUFF_SIZE] = {
    0U,    401U,  799U,  1188U, 1567U, 1930U, 2275U, 2598U, 2895U, 3165U, 3405U, 3611U, 3783U, 3918U, 4016U, 4075U,
    4095U, 4075U, 4016U, 3918U, 3783U, 3611U, 3405U, 3165U, 2895U, 2598U, 2275U, 1930U, 1567U, 1188U, 799U,  401U};
uint16_t g_dacDataArray2[AUDIO_PLAYER_BUFF_SIZE] = {
	2275U, 2275U, 2275U, 2275U, 2275U,2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U,
	2275U, 2275U, 2275U, 2275U, 2275U, 2275U,2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U};

uint32_t iii = 1;
/*!
 * @brief Main function
 */
int test(void)
{

    /* Initialize hardware. */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("DAC CONTINUOUS PDB EDMA DEMO\r\n");

    AudioPlayer_Init();

    /* Generate continuous trigger signal to DAC. */
    //AudioPlayer_DEMOMode(); //Aca iria AudioPlayer_LoadSongInfo(...);


    //AudioPlayer_LoadSongInfo(g_dacDataArray, 12000);

    int16_t baja[1024];
    int i;
  	for(i=0; i<1024; i++)
  	{
  	       //  baja[i] = 30.0f*arm_sin_f32(2*3.1415926f*50*i/44100);
  	         /*
  	         alta[i] = 10.0f*arm_sin_f32(2*3.1415926f*10*i/44100);
  	         otra[i] = 20.0f*arm_sin_f32(2*3.1415926f*100*i/44100);
  	         otra2[i] = 30.0f*arm_sin_f32(2*3.1415926f*200*i/44100);
  	         otra3[i] = 30.0f*arm_sin_f32(2*3.1415926f*300*i/44100);
  	         */
  	         //otra4[i] = 30.0f*arm_sin_f32(2*3.1415926f*15000*i/44100);

  		baja[i] = 1500.0f*sin(2*3.1415926f*130.81*i/44100)+1500;
  	   // signal[i] = baja[i];//+otra4[i];
  	 }



    AudioPlayer_LoadSongInfo(baja, 44100);
    AudioPlayer_Play();
    int lastSent = 1;


    AudioPlayer_UpdateBackBuffer(baja);

    PRINTF("Please probe the DAC output with a oscilloscope.\r\n");
    while (1)
    {
    	if(AudioPlayer_IsBackBufferFree())
    	{

    		AudioPlayer_UpdateBackBuffer(baja);
    		// PARA PROBAR CON ARRAYS DE EJEMPLO:

			//AudioPlayer_UpdateBackBuffer(g_dacDataArray);

    		/*if(lastSent)
    		{
    			AudioPlayer_UpdateBackBuffer(g_dacDataArray);
    			lastSent = 0;
    		}
    		else
    		{
    			AudioPlayer_UpdateBackBuffer(g_dacDataArray2);
    			lastSent = 1;
    		}*/

			/*
    		if(lastSent)
			{
    			for (int i = 0; i < 32; i++)
    			{
    				g_dacDataArray[i] = 2275U;
    			}
				lastSent = 0;
			}
			else
			{
				for (int i = 0; i < 32; i++)
				{
					g_dacDataArray[i] = 3918U;
				}

				lastSent = 1;
			}
			*/


    		//PARA PROBAR CON PEDACITO DE CANCION
    		/*
    		AudioPlayer_UpdateBackBuffer(song + iii * AUDIO_PLAYER_BUFF_SIZE);

    		iii++;

    		if(iii>20000UL)
    		{
    			iii=0;
    		}
    		*/
    	}
    }
}
