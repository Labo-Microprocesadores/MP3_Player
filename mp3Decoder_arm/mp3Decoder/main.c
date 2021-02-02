/***************************************************************************//**
  @file     main.c
  @brief    main file of the mp3 decoder
  @author   Team 2 - Lab de Micros
 ******************************************************************************/

 /*******************************************************************************
  *							INCLUDE HEADER FILES
  ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include "../wav/wav.h"
#include "../mp3Decoder/decoder.h"


 /*******************************************************************************
 *					CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


#define SAMPLE_FORMAT WAV_FORMAT_PCM
 
//here uncomment the others posibilities and select the right song

#define BACH
//#define ODA_A_LA_ALEGRIA
//#define QUEEN


#ifdef BACH
#define FILEPATH		"C:/Users/Usuario/Documents/ITBA/Sebastian-Bach.mp3"
#define FILEPATH_WAV	"C:/Users/Usuario/Documents/ITBA/Sebastian-Bach.wav"
#endif

#ifdef ODA_A_LA_ALEGRIA
#define FILEPATH		"C:/Users/Usuario/Documents/ITBA/Oda-a-la-alegria.mp3"
#define FILEPATH_WAV	"C:/Users/Usuario/Documents/ITBA/Oda-a-la-alegria.wav"
#endif

#ifdef QUEEN
#define FILEPATH		"C:/Users/Usuario/Documents/ITBA/Music/i_want_to_break_free.mp3"
#define FILEPATH_WAV	"C:/Users/Usuario/Documents/ITBA/Music/i_want_to_break_free.wav"
#endif


/*****************************************************************************
 *  					VARIABLES WITH LOCAL SCOPE
 *****************************************************************************/

static short buffer[DECODED_BUFFER_SIZE];

/*******************************************************************************
*                       LOCAL FUNCTION DEFINITIONS
******************************************************************************/

int main(void)
{
	//printf("  MP3 DECODER  \n");
	// it count
	uint16_t sampleCount;
	// if there are 
	uint16_t sampleRate = 0;
	char title[ID3_MAX_NUM_CHARS];                                        // Title of the song
	char artist[ID3_MAX_NUM_CHARS];                                       // Artist of the song
	char album[ID3_MAX_NUM_CHARS];                                        // Album of the song
	uint8_t trackNum[ID3_MAX_NUM_CHARS];                                  // Number of the track inside the album of the song
	uint8_t year[ID3_MAX_NUM_CHARS];                                      // year of the songs album
	uint8_t channelCount;

	// we initializate the data to use the decoder.
	decoder_MP3DecoderInit();

	// if we can open the mp3 file
	if (decoder_MP3LoadFile(FILEPATH))
	{
		if (decoder_hasID3()) {
			//here we get the ID3data in our variables.
			decoder_MP3GetTagData(title, artist, album, trackNum, year);
			// we show the info of the song
			//*************************************************
			//! Here we can use the data to print in the screen
			//*************************************************

			/*printf("\n  SONG INFO\n");
			printf("TITLE: %s\n", ID3Data.title);
			printf("ARTIST: %s\n", ID3Data.artist);
			printf("ALBUM: %s\n", ID3Data.album);
			printf("TRACK NUMBER: %s\n", ID3Data.trackNum);
			printf("YEAR: %s\n \n", ID3Data.year);*/
		}

		// variable frames to count the number of frames decoded
		int frames = 0;
		int reference = 0;
		// ref is to go inside an if inside the while just one time.
		bool ref = false;
		while(true)
		{
			// with this function we update the sampleCount number
			decoder_return_t check = decoder_MP3DecodedFrame(buffer, DECODED_BUFFER_SIZE, &sampleCount);
			if (check == DECODER_WORKED)
			{
				// if there are a last frame get the data
				if (!decoder_MP3GetLastFrameChannelCount(&channelCount)) {
					//if you are here the decoder couldnt get the last frame channel count because there were no last frame it is the fist frame :)
				}
				// we update the number of frames decoded
				
				if (ref == false) {
					// we inform the sample count
					// configutates the wav_file to the right sampleRate according to the information inside the mp3 file.
					// we do it statement here because we need to know the sample rate and we know that after using the MP3GetLastFrameData function
					// set ref in true to not go back here never ever, you are banished from the kingdom of this if
					ref = true;
				}

				// update the counter to share the number of frames decoded at the end of the program
				frames++;

				int16_t auxBuffer[DECODED_BUFFER_SIZE];
				for (uint32_t index = 0; index < (sampleCount / frameData.channelCount); index++)
				{
					auxBuffer[index] = buffer[frameData.channelCount * index];
				}

				// Aqui es donde podemos poner la info del buffer

			}
			else if (check == DECODER_END_OF_FILE)
			{
				break;
			}
		}
	}
	else
	{
		// if you are here the mp3 file couldnt be open
	}
	return 0;
}
