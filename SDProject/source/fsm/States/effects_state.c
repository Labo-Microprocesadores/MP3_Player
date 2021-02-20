/***************************************************************************/ /**
  @file     effects_state.c
  @brief    Effects state functions.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include "States/effects_state.h"
#include "LCD_GDM1602A.h"
#include "queue.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME 2000
#define OPTIONS_ARRAY_SIZE 6
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum
{
    OPEN,
    CONFIG_PIN,
    LOG_OUT,
    CONFIG_DEVICE,
    ADD_USER,
    DEL_USER
} options_t;


/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static bool showingTitle;
static int titleTimerID = -1;
static uint8_t currentOptionIndex = 0;
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
 * @brief Stops showing the title of the state on the display due to a user's interaction.
 */
static void userInteractionStopsTitle(void);

/**
 * @brief Shows the current option in the display.
 */
static void setCurrentOption(void);
/*******************************************************************************
 * FUNCTIONS WITH GLOBAL SCOPE
 ******************************************************************************/

void Effects_InitState(void)
{
	showTitle();
	currentOptionIndex = 0;
}
void Effects_NextOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        uint8_t max = admin ? ADMIN_OPTIONS_ARRAY_SIZE: USER_OPTIONS_ARRAY_SIZE;
        if (currentOptionIndex == max - 1)
            currentOptionIndex = 0;
        else
            currentOptionIndex++;
        setCurrentOption();
    }

}

void Effects_PreviousOption(void)
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

void Effects_SelectOption(void)
{
    if (showingTitle)
        userInteractionStopsTitle();
    else
    {
        SevenSegDisplay_EraseScreen();
        SevenSegDisplay_SetPos(0);
        switch (currentOptionIndex)
        {
            case OPEN:
                emitEvent(OPEN_SELECTED_EV);
                break;
            case CONFIG_DEVICE:
                emitEvent(CONFIG_DEVICE_SELECTED_EV);
                break;
            case ADD_USER:
                emitEvent(ADD_USER_SELECTED_EV);
                break;
            case DEL_USER:
                emitEvent(DELETE_USER_SELECTED_EV);
                break;
            case CONFIG_PIN:
                emitEvent(CONFIG_PIN_SELECTED_EV);
                break;
            case LOG_OUT:
                emitEvent(TIMEOUT_EV);
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
	LCD_clearDisplay();
	LCD_writeStrInPos("Efectos", 7, 0, 0);
	showingTitle = true;
	titleTimerID = Timer_AddCallback(&stopShowingTitle, TITLE_TIME, true);
}

static void stopShowingTitle(void)
{
	showingTitle = false;
	LCD_clearDisplay();
	setCurrentOption();
}

static void userInteractionStopsTitle(void)
{
	Timer_Delete(titleTimerID);
	titleTimerID = -1;
	stopShowingTitle();
}

static void setCurrentOption(void)
{
    SevenSegDisplay_EraseScreen();
    SevenSegDisplay_SetPos(0);
    switch (currentOptionIndex)
    {
    case OPEN:
        SevenSegDisplay_WriteBuffer("OPEN", 4, 0);
        break;
    case CONFIG_DEVICE:
        SevenSegDisplay_WriteBufferAndMove("BRIGHT", 6, 0, BOUNCE);
        break;
    case ADD_USER:
        SevenSegDisplay_WriteBufferAndMove("ADD USER", 8, 0, BOUNCE);
        break;
    case DEL_USER:
        SevenSegDisplay_WriteBufferAndMove("DELETE USER", 11, 0, BOUNCE);
        break;
    case CONFIG_PIN:
        SevenSegDisplay_WriteBufferAndMove("CHANGE PIN", 10, 0, BOUNCE);
        break;
    case LOG_OUT:
        SevenSegDisplay_WriteBufferAndMove("LOG OUT", 7, 0, BOUNCE);
        break;
    }
}


