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
#include "ff.h"
#include "file_system_manager.h"

//incluir el mp3 decoder

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
// Estas dos cosas vienen del mp3 decoder
static uint16_t *currentSongFrame;
static uint16_t sampleRate;

static Mp3File_t currFile;
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

	// esto tendria que ser algo del decoder, tipo un init con el archivo
	// decoder(currFile.path ...);

	// Procesar la siguiente muestra, decode y filtros
	/* fillBuffer();*/

	// Mostrar en el LCD

	/*
	char track[] = "TRACK __";
	track[6] = currFile.index / 10 + '0';
	track[7] = currFile.index % 10 + '0';
	LCD_writeStrInPos(track, 8, 0, 0);
	LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path) - 1, 1, 0, MIDIUM);
	*/

	// Le mando al audio player
	AudioPlayer_LoadSongInfo(currentSongFrame, sampleRate);
	AudioPlayer_Play();
	// Preparo el siguiente frame
	fillBuffer();
}

void Player_Stop(void)
{
  AudioPlayer_Stop();
  //y frenar la fft

  //Tendria que tener algo del decoder que le pida que vuelva al principio del archivo

}
void Player_PlayNextSong(void)
{
  AudioPlayer_Stop();
  // y frenar fft

  // Estas dos cosas vienen del mp3 decoder
  //uint16_t * currentSongFrame = ;//el primer frame de la song
  //uint16_t sampleRate = ;

  // Pido la siguiente cancion al file system y voy a Player Play
  currFile = FileSystem_GetNextFile(currFile);
  Player_Play();
}

void Player_PlayPreviousSong(void)
{
  AudioPlayer_Stop();
  // Pido cancion anterior al file system y voy a Player Play
  currFile = FileSystem_GetPreviousFile(currFile);
  Player_Play();
}
