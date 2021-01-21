/***************************************************************************/ /**
  @file     main_menu_state.c
  @brief    Main Menu state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <fsm/States/main_menu_state.h>
#include "queue.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define OPTIONS_ARRAY_SIZE 3
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum
{
	READ_ST,
    EFFECTS,
	EXIT,
} options_t;
/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static uint8_t currentOptionIndex = 0;
static bool showingTitle;
static int titleTimerID = -1;
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME  2000

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
 */
static void userInteractionStopsTitle(void);

/**
 * @brief Shows the current option of the welcome in the display.
 */
static void setCurrentOption(void);
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/

void mainmenu_initState(void)
{
    showingTitle = false;
    currentOptionIndex = 0;
    showTitle();
}

void mainmenu_nextOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        uint8_t max = OPTIONS_ARRAY_SIZE;
        if (currentOptionIndex == max - 1)
            currentOptionIndex = 0;
        else
            currentOptionIndex++;
        setCurrentOption();
    }
    
}

void mainmenu_previousOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        uint8_t max = OPTIONS_ARRAY_SIZE;
        if (currentOptionIndex == 0)
            currentOptionIndex = max - 1;
        else
            currentOptionIndex--;
        setCurrentOption();
    } 
}

void mainmenu_selectOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
    	//TODO: erase screen
        switch (currentOptionIndex)
        {
            case EXIT:
                emitEvent(TIMEOUT_EV);
                break;
            case EFFECTS:
                emitEvent(EFF_EV);
                break;
            case READ_ST:
                emitEvent(ST_IN_EV);
                break;
        }
    }
    
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
	//TODO: show Title "Menu".
	showingTitle = true;
	titleTimerID = Timer_AddCallback(&stopShowingTitle,TITLE_TIME, true );
}

static void setCurrentOption(void)
{
	//TODO: erase screen.
    switch (currentOptionIndex)
    {
    case EXIT:
    	//TODO: show option on the display
        break;
    case EFFECTS:
    	//TODO: show option on the display
        break;
    case READ_ST:
    	//TODO: show option on the display
        break;
    }


}

static void stopShowingTitle(void)
{
	    showingTitle = false;
	    //   TODO: erase screen
	    setCurrentOption();

}

static void userInteractionStopsTitle(void)
{
		Timer_Delete(titleTimerID);
		titleTimerID = -1;
		stopShowingTitle();
}
