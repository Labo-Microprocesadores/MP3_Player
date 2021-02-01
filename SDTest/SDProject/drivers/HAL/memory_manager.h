/***************************************************************************/ /**
  @file     memory_manager.h
  @brief    Memory System header
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/


#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include <stdbool.h>

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
#define SD_BUFFER_ALIGN_SIZE 	(4U)

/*
 * Callback to buid filesystem
 */
typedef void(*mm_callback)(char * path);
/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

/*
 * Init routine
 * cd: a callback to receive and store the scanned files
 */
void Mm_Init(mm_callback cd);

/*
 * SD present or not
 */
bool Mm_IsSDPresent(void);

#endif /* MEMORY_MANAGER_H_ */
