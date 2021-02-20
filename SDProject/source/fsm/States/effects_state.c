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
#include "Timer.h"

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/
#define TITLE_TIME 2000
#define OPTIONS_ARRAY_SIZE 6


int optionValues[5][8] =
	{{0, 0, 0, 0, 0, 0, 0, 0}, 		//default
	{0, 0, 1, 3, -10, -2, -1, 3}, 	//rock
	{0, 0, 2 , 5, -6, -2, -1, 2},	//jazz
	{0, 0, 0, 0, 2, 2, 3, -3},		//pop
	{0, 0, -1, -6, 0, 1, 1, 3}		//classic
};
/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
typedef enum
{
	DEFAULT,
	ROCK,
	JAZZ,
	POP,
	CLASSIC,
	CUSTOM
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
        uint8_t max = OPTIONS_ARRAY_SIZE;
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
    	LCD_clearDisplay();
        if (currentOptionIndex == OPTIONS_ARRAY_SIZE-1)
        {
        	//custom
        }else
        {
        	//access values: optionValues[currentOptionIndex]
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
    LCD_clearDisplay();
    switch (currentOptionIndex)
    {
    case ROCK:
    	LCD_writeStrInPos("ROCK                ", 16, 0, 0);
        break;
    case JAZZ:
    	LCD_writeStrInPos("JAZZ                ", 16, 0, 0);
        break;
    case POP:
    	LCD_writeStrInPos("POP                 ", 16, 0, 0);
        break;
    case CUSTOM:
    	LCD_writeStrInPos("CUSTOM              ", 16, 0, 0);
		break;
    }
}


