/***************************************************************************/ /**
  @file     player_state.h
  @brief    Player state header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include "../../fsm.h"

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void player_initFSM(void);

void player_onLKP(void);
void player_onPress(void);
void player_onStorageOut(void);
void player_onTimeOut(void);

#endif /* PLAYER_STATE_H*/
