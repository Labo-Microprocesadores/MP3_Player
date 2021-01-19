/*******************************************************************************
  @file     file_selection_state.h
  @brief   	File Selection state header
  @author   Grupo 2 - Lab de Micros
 **********/
#ifndef FILE_SELECTION_STATE_H
#define FILE_SELECTION_STATE_H

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdint.h>


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/**
 * @brief Initialization of the state.
 */
void fileselection_initState(void);
/**
 * @brief If a folder is selected, go inside of it. If it's a file, read it.
 */
void fileselection_goIn(void);
/**
 * @brief Go out of the current folder (if possible).
 */
void fileselection_goOut(void);


#endif //FILE_SELECTION_STATE_H
