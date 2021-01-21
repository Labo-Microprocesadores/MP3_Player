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
#include "file_selection_state.h"
#include "queue.h"
/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static bool showingTitle;
static int titleTimerID = -1;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Show the title of the state on the display. If the user interacts with the system, the title will stop showing.
 */
static void showTitle(void);
/**
 * @brief Stops showing the title of the state on the display.
 */
static void stopShowingTitle(void);

/**
 * @brief Stops showing the title of the state in the display due to a user's interaction.
 * The main reason of creating another function for this is to avoid cancelling a callback (of the timer) inside of it (callback).
 */
static void userInteractionStopsTitle(void);

/*
 * @brief Gets the file tree and shows the main node name.
 */
static void showFiles(void);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void fileselection_initState(void)
{
    showTitle();    //Shows the state's title.
}
void fileselection_goIn(void)
{
	 if (showingTitle)
		userInteractionStopsTitle();
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
	//TODO: show Title "Select File".
	showingTitle = true;
	titleTimerID = Timer_AddCallback(&stopShowingTitle,TITLE_TIME, true );
}


static void stopShowingTitle(void)
{
	    showingTitle = false;
	    //   TODO: erase screen
	    showFiles();

}

static void userInteractionStopsTitle(void)
{
		Timer_Delete(titleTimerID);
		titleTimerID = -1;
		stopShowingTitle();
}

static void showFiles(void)
{
	//TODO: get the file tree and show the main node.
}

