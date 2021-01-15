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


/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/

void Mm_Init(void);

char * Mm_GetCurrentPath(void);
char * Mm_GetCurrentName(void);

void Mm_GoNext(void);
bool Mm_IsNext(void);

void Mm_GoPrev(void);
bool Mm_IsPrev(void);

void Mm_GoInDir(void);
void Mm_GoOutDir(void);

bool Mm_CanGoInDir(void);
bool Mm_CanGoOutDir(void);

#endif /* MEMORY_MANAGER_H_ */
