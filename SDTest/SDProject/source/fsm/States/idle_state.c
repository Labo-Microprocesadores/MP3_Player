/***************************************************************************/ /**
  @file     idle_state.c
  @brief    Idle state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "idle_state.h"
#include "queue.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Show the current time on the display. If the user interacts with the system, the time will stop showing.
 */
static void showTime(void);
/**
 * @brief Stops showing the time on the display.
 */
static void stopShowingTime(void);
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/

void idle_initState(void)
{

    showTime();
    //TODO: enter low energy consumption mode.
}

void idle_onUserInteraction(void)
{
	//TODO: enter high energy consumption mode.
	stopShowingTime();
	emitEvent(START_EV);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTime(void)
{
	//TODO: fetch current time and show it on the display.
}


static void stopShowingTime(void)
{
	//When the user interacts with the system, stop showing the time
}

