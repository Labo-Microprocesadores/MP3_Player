/***************************************************************************//**
  @file     board.h
  @brief    Board management
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef _BOARD_H_
#define _BOARD_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "gpio.h"


/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/***** BOARD defines **********************************************************/

// On Board User LEDs
#define PIN_LED_RED     PORTNUM2PIN(PB,22) // PTB22
#define PIN_LED_GREEN   PORTNUM2PIN(PE,26) // PTE26
#define PIN_LED_BLUE    PORTNUM2PIN(PB,21) // PTB21

#define LED_ACTIVE      LOW


// On Board User Switches
#define PIN_SW2         PORTNUM2PIN(PC,6) // PTC6
#define PIN_SW3         PORTNUM2PIN(PA,4) // PTA4

#define SW_ACTIVE       LOW
#define SW_INPUT_TYPE   INPUT_PULLDOWN

#define PIN_SW_A		PORTNUM2PIN(PC,10)
#define PIN_SW_B		PORTNUM2PIN(PC,11)
#define PIN_SW_C		PORTNUM2PIN(PB,11)
#define PIN_SW_D		PORTNUM2PIN(PB,10)

// Encoder pin's
#define ENCODER_A		PORTNUM2PIN(PB,2) // PTC8
#define ENCODER_B		PORTNUM2PIN(PB,20) // PTC9
#define ENCODER_SW  	PORTNUM2PIN(PB,3)// PTB18


// Test point
#define TP				PORTNUM2PIN(PC,4) // PTC4

/*******************************************************************************
 ******************************************************************************/

#endif // _BOARD_H_
