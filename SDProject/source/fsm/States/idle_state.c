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
#include "power_mode_switch.h"
#include "LCD_GDM1602A.h"
#include "time_service.h"
#include "Timer.h"
#include "memory_manager.h"

#include "audio_manager.h"
#include "LCD_GDM1602A.h"

/*********************************************************
 * 		LOCAL STRUCTS AND ENUMS
 ********************************************************/
typedef enum
{
  LOW_CONSUMPTION,
  HIGH_CONSUMPTION,
} EnergyConsumptionMode_t;

/*******************************************************************************
 * PRIVATE VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
int timeCallbackId = -1;
/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Shows the current time on the display.
 */
static void showTime(void);
/**
 * @brief Stops showing the time on the display.
 */
static void stopShowingTime(void);

/**
 * @brief Changes the energy consumption mode of the device.
 * @param EnergyConsumptionMode_t energy mode.
 */
static void setEnergyConsumptionMode(EnergyConsumptionMode_t energyConsumptionMode);

/**
 * @brief Fetches the current time and shows it on the display.
 */
static void updateDisplayTime();

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void Idle_InitState(void)
{
	Audio_deinit();

	LCD_stopMove(0);
	LCD_stopMove(1);

	char dateString[16] = "   18-01-2019   ";
	char timeString[16] =  "     12:04      ";
	//LCD_clearDisplay();
	LCD_writeStrInPos(timeString, 16, 0, 0);
	LCD_writeStrInPos(dateString, 16, 1, 0);

	setEnergyConsumptionMode(LOW_CONSUMPTION);
	//LCD_UpdateClock();

	//showTime();
}

void Idle_OnUserInteraction(void)
{
	if (!Mm_IsSDPresent())
		return;

	setEnergyConsumptionMode(HIGH_CONSUMPTION);
	//PowerMode_SetRunMode();
	stopShowingTime();
	//LCD_UpdateClock();
	emitEvent(START_EV);
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTime(void)
{
  updateDisplayTime();
  timeCallbackId = Timer_AddCallback(updateDisplayTime, 100, false);
}

static void updateDisplayTime()
{
	return;
  TimeServiceDate_t date = TimeService_GetCurrentDateTime();

  char dateString[16];
  char timeString[16];
  snprintf(dateString, sizeof(dateString), "   %02hd-%02hd-%04hd   ", date.day, date.month, date.year);
  snprintf(timeString, sizeof(timeString), "     %02hd:%02hd      ", date.hour,
		   date.minute);

  //LCD_clearDisplay();
  LCD_writeStrInPos(timeString, 16, 0, 0);
  LCD_writeStrInPos(dateString, 16, 1, 0);
  //printf("%s\n%s\n", timeString, dateString);
}

static void stopShowingTime(void)
{
  Timer_Delete(timeCallbackId);
  //LCD_clearDisplay();

}

static void setEnergyConsumptionMode(EnergyConsumptionMode_t energyConsumptionMode)
{
  switch (energyConsumptionMode)
  {
  case LOW_CONSUMPTION:
	  PowerMode_SetVLPRMode();
    break;

  case HIGH_CONSUMPTION:
	  PowerMode_SetRunMode();
    break;

  default:
    break;
  }
}
