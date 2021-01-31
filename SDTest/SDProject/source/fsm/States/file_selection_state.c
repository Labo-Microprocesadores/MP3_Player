/***************************************************************************/ /**
  @file     file_selection_state.c
  @brief    File Selection State Functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define TITLE_TIME  5000

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdbool.h>
#include "file_selection_state.h"
#include "queue.h"
#include "AudioPlayer.h"
//incluir mp3 decoder

/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static bool showingTitle;
static int titleTimerID = -1;
uint16_t * firstSongFrame;
uint16_t sampleRate;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
/**
 * @brief Show the title of the state on the display. If the user interacts with the system, the title will stop showing.
 */
static void showTitle(void);
/**
 * @brief Stops showing the title of the state on the display.
 */
static void stopShowingTitle(void);

/**
 * @brief Stops showing the title of the state in the display due to a user's interaction.
 * The main reason of creating another function for this is to avoid cancelling a callback (of the timer) inside of it (callback).
 */
static void userInteractionStopsTitle(void);

/**
 * @brief Fetches the files that exist in the current SD.
 */
static void initialFileFetching(void);

/**
 * @brief Prints the file's name and artist
 */
static void printFileInfo(void);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void FileSelection_initState(void)
{
    showTitle();    //Shows the state's title.
	titleTimerID = Timer_AddCallback(&stopShowingTitle,TITLE_TIME, true );
    
}

void FileSelection_NextFile(void)
{
	//TODO: get file.
	printFileInfo();//TODO: add file parameter.
}

void FileSelection_PreviousFile(void)
{
	//TODO: get file.
	printFileInfo();//TODO: add file parameter.
}


void FileSelection_SelectFile(void)
{
	// Estas dos cosas vienen del mp3 decoder
	//uint16_t * firstSongFrame = ;
	//uint16_t sampleRate = ;
	f_open(&g_fileObject, _T(currFile.path), (FA_READ));
	fillBuffer();

	char track[] = "TRACK __";
	track[6] = currFile.index/10 + '0';
	track[7] = currFile.index%10 + '0';
	//LCD_writeStrInPos(track, 8, 0, 0);
	LCD_writeBouncingStr(&currFile.path[1], strlen(currFile.path)-1, 1, 0, MIDIUM);

	AudioPlayer_LoadSongInfo(firstSongFrame, sampleRate);
	AudioPlayer_Play();
	fillBuffer();
}
/*******************************************************************************
 *******************************************************************************
 *                         LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
static void showTitle(void)
{
	LCD_clearDisplay();
	LCD_writeStrInPos("Elegir Archivo", 14, 0 , 0);
	showingTitle = true;
	titleTimerID = Timer_AddCallback(&stopShowingTitle,TITLE_TIME, true );
}


static void stopShowingTitle(void)
{
	    showingTitle = false;
	    LCD_clearDisplay();
	    showFiles();
}

static void userInteractionStopsTitle(void)
{
		Timer_Delete(titleTimerID);
		titleTimerID = -1;
		stopShowingTitle();
}

static void initialFileFetching(void)
{
	//TODO: fetch files.
	printFileInfo(); //TODO: send first file
}

    //TODO: Add file parameter
static void printFileInfo(void)
{
	    //TODO: Show the file's name and data.
		LCD_writeStrInPos("Archivo Prueba", 14, 0 , 0);
		LCD_writeStrInPos("Artista Prueba", 14, 0 , 0);
}


