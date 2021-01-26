

#include "AudioPlayer.h"
#include "fsl_debug_console.h"

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
    AudioPlayer_Play();

    PRINTF("Please probe the DAC output with a oscilloscope.\r\n");
    while (1)
    {
    }
}
