/***************************************************************************/ /**
  @file    	pause_state.c
  @brief    Pause state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "pause_state.h"
#include "queue.h"

/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/
void pause_Pause(void)
{
	//TODO: pause mp3 file
	//TODO: show "pause" message on the display
}

void pause_changeEffects(void)
{
	pause_Pause();
	emitEvent(EFF_EV);
}
