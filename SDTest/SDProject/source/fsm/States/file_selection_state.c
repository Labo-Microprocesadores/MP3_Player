/***************************************************************************/ /**
  @file     file_selection_state.c
  @brief    File Selection State Functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define TITLE_TIME  5000

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
//#include "timer.h"
#include "file_selection_state.h"
//#include "data_base.h"
#include "queue.h"
//#include "seven_seg_display.h"


/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static bool showingTitle, showingErrorIndication;
static int titleTimerID = -1;
static int errorIndicationTimerID = -1;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Show the title of the state in the display. If the user interacts with the system, the title will stop showing and the input will start.
 */
static void showTitle(void);
/**
 * @brief Stops showing the title of the state in the display. The input starts.
 */
static void stopShowingTitle(void);

/**
 * @brief Stops showing the title of the state in the display due to a user's interaction. The input starts.
 * The main reason of creating another function for this is to avoid cancelling a callback (of the timer) inside of it (callback).
 */
static void userInteractionStopsTitle(void);

/**
 * @brief Stops showing the error indication in the display due to a user's interaction. The state 'restarts'.
 */
static void userInteractionStopsErrorIndication(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
//!OJO EN TODAS ESTADS HABRIA QUE RESETEAR EL TIMER DE TIMEOUT Y EN ALGUNAS ACTUALIZAR EL DISPLAY
//TODO AGREGAR ESO

void fileselection_initState(void)
{
    showingErrorIndication = false;
    showTitle();    //Shows the state's title.
}
void fileselection_goIn(void)
{
	 if (showingTitle)
		userInteractionStopsTitle();
	else if (showingErrorIndication)
		userInteractionStopsErrorIndication();
	else
	{
		//Go inside folder or read file
		//if (file)
		//	emitEvent(PLAY_EV);
	}

}
void fileselection_goOut(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else if (showingErrorIndication)
        userInteractionStopsErrorIndication(); 
    else
    {
    	//Go out of the current folder
    }
    
}


/*******************************************************************************
 *******************************************************************************
 *                         LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
//    SevenSegDisplay_EraseScreen();
//    SevenSegDisplay_SetPos(0);
//    SevenSegDisplay_CursorOff();
//    SevenSegDisplay_WriteBufferAndMove("SELECT FILE, 11, 0, BOUNCE);    //Shows title.
//    showingTitle = true;
//    titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);  //Sets the callback to stop the title and start the input.
}

static void stopShowingTitle(void)
{
//    SevenSegDisplay_EraseScreen();
//    SevenSegDisplay_SetPos(0);
//    showingTitle = false;
}

static void userInteractionStopsTitle(void)
{
//    Timer_Delete(titleTimerID); //Cancels the callback.
//    titleTimerID = -1;
//    stopShowingTitle();
}


static void userInteractionStopsErrorIndication(void)
{
//    SevenSegDisplay_EraseScreen();
//    Timer_Delete(errorIndicationTimerID);   //Cancels the callaback.
//    showingErrorIndication = false;
//    errorIndicationTimerID = -1;
//    fileselection_initState();   //Starts the state's cycle again.
}
