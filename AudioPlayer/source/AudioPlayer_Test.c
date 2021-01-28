

#include "AudioPlayer.h"
#include "fsl_debug_console.h"

extern uint16_t song;




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
int main(void)
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
    AudioPlayer_LoadSongInfo(song, 44100);
    AudioPlayer_Play();
    int lastSent = 1;


    PRINTF("Please probe the DAC output with a oscilloscope.\r\n");
    while (1)
    {
    	if(AudioPlayer_IsBackBufferFree())
    	{

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
    		AudioPlayer_UpdateBackBuffer(song + iii * AUDIO_PLAYER_BUFF_SIZE);

    		iii++;

    		if(iii>20000UL)
    		{
    			iii=0;
    		}
    	}
    }
}
