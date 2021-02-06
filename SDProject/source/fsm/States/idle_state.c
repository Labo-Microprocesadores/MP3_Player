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

/*********************************************************
 * 		LOCAL STRUCTS AND ENUMS
 ********************************************************/
typedef enum
{
  LOW_CONSUMPTION,
  HIGH_CONSUMPTION,
} EnergyConsumptionMode_t;

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

/**
 * @brief Changes the energy consumption mode of the device.
 * @param EnergyConsumptionMode_t energy mode.
 */
static void setEnergyConsumptionMode(EnergyConsumptionMode_t energyConsumptionMode);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void Idle_InitState(void)
{

  showTime();
  setEnergyConsumptionMode(LOW_CONSUMPTION);
}

void Idle_OnUserInteraction(void)
{
  setEnergyConsumptionMode(HIGH_CONSUMPTION);
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
  LCD_clearDisplay();
  LCD_writeStrInPos("20:03PM", 7, 0, 0);
  LCD_writeStrInPos("31/01/21", 8, 1, 0);
}

static void stopShowingTime(void)
{
  LCD_clearDisplay();
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
