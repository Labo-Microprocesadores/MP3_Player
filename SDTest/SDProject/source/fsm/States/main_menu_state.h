/***************************************************************************/ /**
  @file     main_menu_state.h
  @brief    main_menu state
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/
#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdint.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
/**
 * @brief Initializes the main menu state
 */
void mainmenu_initState(void);
/**
 * @brief Changes the current position of the options array to the next one.
 */
void mainmenu_nextOption(void);
/**
 * @brief  Changes the current position of the options array to the previous one.
 */
void mainmenu_previousOption(void);

/**
 * @brief Selects the current option. Adds an event to the event queue of the FSM.
 */
void mainmenu_selectOption(void);

#endif /* MAIN_MENU_STATE_H */
