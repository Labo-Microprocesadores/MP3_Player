/***************************************************************************/ /**
  @file     Player_state.h
  @brief    Player state header.
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

/*******************************************************************************
 * FUNCTION PROTOTYPES WITH GLOBAL SCOPE
 ******************************************************************************/
void Player_InitState(void);
void Player_Pause(void);
void Player_Play(void);
void Player_Stop(void);
void Player_PlayNextSong(void);
void Player_PlayPreviousSong(void);

#endif /* PLAYER_STATE_H*/
