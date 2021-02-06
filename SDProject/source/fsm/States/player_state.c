/***************************************************************************/ /**
  @file     add_user.c
  @brief    add user state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <fsm/States/player_state.h>
#include <stdbool.h>
#include <string.h>

#include "queue.h"
#include "audio_manager.h"

#include "vumeterRefresh.h"

#include "AudioPlayer.h"
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
	Audio_pause();
}

void Player_Play(void)
{
/*	AudioPlayer_LoadSongInfo(currentSongFrame, sampleRate);
	AudioPlayer_Play();
	// Preparo el siguiente frame
	fillBuffer();*/
}

void Player_Stop(void)
{
	Audio_stop();
}

void Player_PlayNextSong(void)
{
	Audio_nextFile();
	Audio_selectFile();
	Audio_play();
}

void Player_PlayPreviousSong(void)
{
	Audio_prevFile();
	Audio_selectFile();
	Audio_play();
}

static void printFileInfo(void)
{
	char path[50], data[400];
	memset(data, 0x20, 400);
	memset(path, 0x20, 50);
	char * name = Audio_getCurrentName();
	char * artist = Audio_getArtist();
	char * album = Audio_getAlbum();
	char * year = Audio_getYear();
	char * gather[] = {"Artista: ", artist, " Album: ", album, " Año: ", year};

	uint16_t len = strlen(name);
	len += (DISPLAY_COLUMNS-(len%DISPLAY_COLUMNS));
	memcpy(path, name, strlen(name));
	LCD_writeShiftingStr(path,  len, 0, MIDIUM);



	len = 0;
	for(int k = 0; k < sizeof(gather)/sizeof(gather[0]); k++)
	{
		memcpy(data + len, gather[k], strlen(gather[k]));
		len += strlen(gather[k]);
	}
	len += (DISPLAY_COLUMNS-(len%DISPLAY_COLUMNS));
	LCD_writeShiftingStr(data,  len, 1, MIDIUM);

}

