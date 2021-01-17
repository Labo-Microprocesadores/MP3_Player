/***************************************************************************/ /**
  @file     main_effects_state.c
  @brief    Main Effects state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "main_effects_state.h"
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
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/

void maineffects_initState(void)
{
    showingTitle = false;
    showTitle();
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
//    SevenSegDisplay_EraseScreen();
//    SevenSegDisplay_CursorOff();
//    SevenSegDisplay_SetPos(0);
//    SevenSegDisplay_WriteBufferAndMove("EFFECTS", 6, 0, BOUNCE);
//    Led_Off(LED_BLUE);
//    Led_InfiniteBlink(LED_GREEN, NORMAL);
//    titleTimerID = Timer_AddCallback(&stopShowingTitle,TITLE_TIME, true );
}


static void stopShowingTitle(void)
{
//    SevenSegDisplay_EraseScreen();
//    showingTitle = false;
//    setCurrentOption();
//    Led_StopInfiniteBlink(LED_GREEN);
//    Led_On(LED_BLUE);
}

static void userInteractionStopsTitle(void)
{
//    Timer_Delete(titleTimerID);
//    titleTimerID = -1;
//    stopShowingTitle();
}
