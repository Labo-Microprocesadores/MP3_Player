/***************************************************************************/ /**
  @file     add_user.c
  @brief    add user state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <fsm/States/Player_state.h>
#include <stdbool.h>
#include "queue.h"
#include "AudioPlayer.h"
#include "vumeterRefresh.h"
//incluir el mp3 decoder

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
// Estas dos cosas vienen del mp3 decoder
uint16_t *currentSongFrame;
uint16_t sampleRate;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 **********************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void Player_InitState(void)
{
}
void Player_Pause(void)
{
  AudioPlayer_Pause();
  // y frenar la fft.
}
void Player_Play(void)
{
  // Estas dos cosas vienen del mp3 decoder
  //uint16_t * firstSongFrame = ;
  //uint16_t sampleRate = ;
  f_open(&g_fileObject, _T(currFile.path), (FA_READ));
  fillBuffer();

  char track[] = "TRACK __";
  track[6] = currFile.index / 10 + '0';
  track[7] = currFile.index % 10 + '0';
  //LCD_writeStrInPos(track, 8, 0, 0);
  LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);

  AudioPlayer_LoadSongInfo(currentSongFrame, sampleRate);
  AudioPlayer_Play();
  fillBuffer();
}
void Player_Stop(void)
{
  AudioPlayer_Stop();
  //y frenar la fft

  // Estas dos cosas vienen del mp3 decoder
  //uint16_t * currentSongFrame = ;//el primer frame de la song
  //uint16_t sampleRate = ;
  f_open(&g_fileObject, _T(currFile.path), (FA_READ));
  fillBuffer();

  char track[] = "TRACK __";
  track[6] = currFile.index / 10 + '0';
  track[7] = currFile.index % 10 + '0';
  //LCD_writeStrInPos(track, 8, 0, 0);
  LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);

  AudioPlayer_LoadSongInfo(currentSongFrame, sampleRate); // mandarle el primer frame
  AudioPlayer_Play();
  fillBuffer();
}
void Player_PlayNextSong(void)
{
  AudioPlayer_Stop();
  // y frenar fft

  currFile++;
  // Estas dos cosas vienen del mp3 decoder
  //uint16_t * currentSongFrame = ;//el primer frame de la song
  //uint16_t sampleRate = ;
  f_open(&g_fileObject, _T(currFile.path), (FA_READ));
  fillBuffer();

  char track[] = "TRACK __";
  track[6] = currFile.index / 10 + '0';
  track[7] = currFile.index % 10 + '0';
  //LCD_writeStrInPos(track, 8, 0, 0);
  LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);

  AudioPlayer_LoadSongInfo(currentSongFrame, sampleRate); // mandarle el primer frame
  AudioPlayer_Play();
  fillBuffer();
}

void Player_PlayPreviousSong(void)
{
  AudioPlayer_Stop();
  currFile--;
  // Estas dos cosas vienen del mp3 decoder
  //uint16_t * currentSongFrame = ;//el primer frame de la song
  //uint16_t sampleRate = ;
  f_open(&g_fileObject, _T(currFile.path), (FA_READ));
  fillBuffer();

  char track[] = "TRACK __";
  track[6] = currFile.index / 10 + '0';
  track[7] = currFile.index % 10 + '0';
  //LCD_writeStrInPos(track, 8, 0, 0);
  LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);

  AudioPlayer_LoadSongInfo(currentSongFrame, sampleRate); // mandarle el primer frame
  AudioPlayer_Play();
  fillBuffer();
}
