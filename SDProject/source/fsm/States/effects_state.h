/***************************************************************************/ /**
  @file     effects_state.h
  @brief    Effects state
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef EFFECTS_STATE_H
#define EFFECTS_STATE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initializes the main effects state
 */
void Effects_InitState(void);

/**
 * @brief Shows the next option.
 */
void Effects_NextOption(void);
/**
 * @brief Shows the previous option.
 */
void Effects_PreviousOption(void);

/**
 * @brief Selects the current option. Adds an event to the event queue of the FSM.
 */
void Effects_SelectOption(void);


void Effects_Back(void);

#endif /* EFFECTS_STATE_H */
