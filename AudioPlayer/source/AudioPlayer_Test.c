

#include "AudioPlayer.h"
#include "fsl_debug_console.h"

#define DEMO_DAC_USED_BUFFER_SIZE 32U

uint16_t g_dacDataArray[DEMO_DAC_USED_BUFFER_SIZE] = {
    0U,    401U,  799U,  1188U, 1567U, 1930U, 2275U, 2598U, 2895U, 3165U, 3405U, 3611U, 3783U, 3918U, 4016U, 4075U,
    4095U, 4075U, 4016U, 3918U, 3783U, 3611U, 3405U, 3165U, 2895U, 2598U, 2275U, 1930U, 1567U, 1188U, 799U,  401U};
uint16_t g_dacDataArray2[DEMO_DAC_USED_BUFFER_SIZE] = {
	2275U, 2275U, 2275U, 2275U, 2275U,2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U,
	2275U, 2275U, 2275U, 2275U, 2275U, 2275U,2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U, 2275U};

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
    AudioPlayer_LoadSongInfo(g_dacDataArray, g_dacDataArray2, DEMO_DAC_USED_BUFFER_SIZE, 8000);
    AudioPlayer_Play();
    int lastSent = 1;

    PRINTF("Please probe the DAC output with a oscilloscope.\r\n");
    while (1)
    {
    	if(AudioPlayer_IsBackBufferFree())
    	{
    		if(lastSent)
    		{
    			AudioPlayer_UpdateBackBuffer(g_dacDataArray);
    			lastSent = 0;
    		}
    		else
    		{
    			AudioPlayer_UpdateBackBuffer(g_dacDataArray2);
    			lastSent = 1;
    		}
    	}
    }
}
