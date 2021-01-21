/***************************************************************************/ /**
  @file     idle_state.h
  @brief    Idle state
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef IDLE_STATE_H
#define IDLE_STATE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initializes the idle state
 */
void idle_initState(void);

/**
 * @brief Stop showing the time when the user interacts with the system.
 */
void idle_onUserInteraction(void);


#endif /* IDLE_STATE_H */
