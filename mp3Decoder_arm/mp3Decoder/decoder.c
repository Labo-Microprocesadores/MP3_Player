/*******************************************************************************
  @file     decoder.c
  @brief    file with the decoder function to use the library helix
  @author   Team 2 - Lab de Micros
 ******************************************************************************/

 /*******************************************************************************
  *							INCLUDE HEADER FILES
  ******************************************************************************/

#include <string.h>
#include <stdbool.h> 
#include "../fatfs/ff.h"
#include "decoder.h"
#include  "../helix/pub/mp3dec.h"
#include "../id3/read_id3.h"

 /*******************************************************************************
 *					CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define FRAME_BYTES 5000

#define DECODER_NORMAL_MODE 0

#define ErrorGettingNextFrameInfo 0

#define DEFAULT_ID3 "Unknown"

/*******************************************************************************
 *      FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

 /*
 * @brief  Open the file to read the information inside
 * @returns  the number of bytes of the file
 */
static bool decoder_openFile(const char* filename);
/*
* @brief  calculate the number of bytes of the file
* @returns  the number of bytes of the file
*/
static size_t decoder_fileSize(void);

/*
* @brief  This function fills buffer with info encoded in mp3 file and update the pointers
*/


/**
 * @brief check if the file is open and read as much data as passed in count parameter
 * @params buf: here we store the data 
 * @params count: the number of data to be readed
 */
static size_t decoder_readFile(void* buf, size_t count);

/*
* @brief  This function fills buffer with info encoded in mp3 file and update the pointers
*/
static void decoder_ToBuffer(void);

/*
* @brief  This function reads the ID3 Tag of the file if it has and move the read position according to the size of the ID3Tag to avoid read it twice
*/
void decoder_readID3Tag(void);

/*****************************************************************************
 *  					VARIABLES WITH LOCAL SCOPE
 *****************************************************************************/

// Helix data
static HMP3Decoder   helixDecoder;                                   // Helix MP3 decoder instance 
static MP3FrameInfo  lastFrameInfo;                                  // MP3 frame info
// MP3 file data
static FIL* mp3File;										      // MP3 file object
static uint32_t      fileSize;                                       // Size of the file used
static uint32_t      bytesRem;									      // Encoded MP3 bytes remaining to be decoded
static bool          fileOpened;                                     // true if there is an open file, false if is not
static uint32_t      lastFrameLength;                                // Last frame length
// MP3-encoded buffer data
static uint8_t       mp3FrameBuffer[FRAME_BYTES];					  // buffer for MP3-encoded frames
static uint32_t      topPosition;                                    // current position in frame buffer (points to top)
static uint32_t      bottomPosition;                                 // current position at info end in frame buffer
// ID3 tag data
static bool                  hasID3;								  // True if the file has valid ID3 tag
char title[ID3_MAX_NUM_CHARS];                                        // Title of the song
char artist[ID3_MAX_NUM_CHARS];                                       // Artist of the song
char album[ID3_MAX_NUM_CHARS];                                        // Album of the song
uint8_t trackNum[ID3_MAX_NUM_CHARS];                                  // Number of the track inside the album of the song
uint8_t year[ID3_MAX_NUM_CHARS];                                      // year of the songs album


/*******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 ******************************************************************************/

void decoder_MP3DecoderInit(void)
{
    helixDecoder = MP3InitDecoder();
    mp3File = NULL;
    fileOpened = false;
    bottomPosition = 0;
    topPosition = 0;
    fileSize = 0;
    bytesRem = 0;
    hasID3 = false;
}


bool decoder_MP3LoadFile(const char* filename)
{
    // he is gulty I don't have any proof but I don�t have any doubts either 
    bool check = false;

    // if the file was open
    if (fileOpened)
    {
        // Close the file 
        f_close(mp3File);

        // Reset pointers and variables 
        fileOpened = false;
        bottomPosition = 0;
        topPosition = 0;
        fileSize = 0;
        bytesRem = 0;
        hasID3 = false;
    }

    // try to open the file an if it can modify the variables inside decoder.
    if (openFile(filename))
    {
        fileOpened = true;
        fileSize = decoder_fileSize();
        // because is the first time there are fileSize numbers of bytes remaining for the decoder
        bytesRem = fileSize;

        // We read the data stored in the tag of the mp3 file
        readID3Tag();

        // flush file to buffer
        ToBuffer();


        // every worked okey
        check = true;
    }
    return check;
}

decoder_return_t decoder_MP3DecodedFrame(short* outBuffer, uint16_t bufferSize, uint16_t* Decodedsamples)
{
    // someone is innocent until proven guilty. 
    decoder_return_t check = DECODER_WORKED;

    if (!fileOpened)
    {
        check = DECODER_NO_FILE;
    }
    // checks if there is still a part of the file to be decoded
    else if (bytesRem)
    {
        // checks if the conditions are fine
        if ((topPosition > 0) && ((bottomPosition - topPosition) > 0) && (bottomPosition - topPosition < FRAME_BYTES))
        {
            memmove(mp3FrameBuffer, mp3FrameBuffer + topPosition, bottomPosition - topPosition);
            bottomPosition = bottomPosition - topPosition;
            topPosition = 0;
        }
        // Read data from file
        ToBuffer();
        // search the mp3 header
        int offset = MP3FindSyncWord(mp3FrameBuffer + topPosition, bottomPosition);
        if (offset >= 0)
        {
            // check errors in searching for sync words 
            topPosition += offset;
            bytesRem -= offset;  //! subtract garbage 
        }
        // check samples in next frame
        MP3FrameInfo nextFrameInfo;
        // with this function we store the nextFrameInfo data in our struct
        int err = MP3GetNextFrameInfo(helixDecoder, &nextFrameInfo, mp3FrameBuffer + topPosition);
        if (err == ErrorGettingNextFrameInfo)
        {
            if (nextFrameInfo.outputSamps > bufferSize)
            {
                return DECODER_OVERFLOW;
            }
        }
        // we can now decode a frame
        uint8_t* decPointer = mp3FrameBuffer + topPosition;
        int bytesLeft = bottomPosition - topPosition;
        // the next funtion autodecrements fileSize with bytes decoded and updated bytesLeft
        int res = MP3Decode(helixDecoder, &decPointer, &(bytesLeft), outBuffer, DECODER_NORMAL_MODE);

        // if everithing worked okey
        if (res == ERR_MP3_NONE)
        {
            // we calculate the bytes decoded
            uint16_t decodedBytes = bottomPosition - topPosition - bytesLeft;
            lastFrameLength = decodedBytes;

            // update pointers and the numb of bytes that left to decode.
            topPosition += decodedBytes;
            bytesRem -= decodedBytes;

            // update last frame decoded data
            MP3GetLastFrameInfo(helixDecoder, &(lastFrameInfo));

            // update num of samples decoded
            *Decodedsamples = lastFrameInfo.outputSamps;
            check = DECODER_WORKED;
        }
        else if (res == ERR_MP3_INDATA_UNDERFLOW || res == ERR_MP3_MAINDATA_UNDERFLOW)
        {
            if (bytesRem == 0)
            {
                printf("buffer underflow error");
                return DECODER_END_OF_FILE;
            }
        }
        else
        {
            if (bytesRem <= lastFrameLength)
            {
                //if you are here it means that you ended the file
                return DECODER_END_OF_FILE;
            }
            else
            {
                printf("Error");
            }
        }
    }
    else
    {
        // if you are here it means that you ended the file
        check = DECODER_END_OF_FILE;
    }
    return check;
}

bool decoder_MP3GetLastFrameChannelCount(uint8_t* channelCount)
{
    // we assume that there are no last frame.
    bool ret = false;
    if (bytesRem < fileSize)
    {
        *channelCount = lastFrameInfo.nChans;
        ret = true;
    }
    return ret;
}

void decoder_MP3GetTagData(char* title_, char* album_, char* artist_, uint8_t* trackNum_, uint8_t* year_)
{
    strcpy(album, album);
    strcpy(artist, artist);
    strcpy(title, title);
    strcpy(trackNum, trackNum);
    strcpy(year, year);
}

bool decoder_hasID3(void) {
    return hasID3;
}

/*******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 ******************************************************************************/

bool decoder_openFile(const char* filename)
{
    FRESULT fr = f_open(mp3File, filename, FA_READ);
    if (fr == FR_OK)
        return true;
    return false;
}

size_t decoder_fileSize()
{
    size_t result = 0;
    if (fileOpened)
    {
        // There may be an error on this line
        f_size(mp3File);
    }
    return result;
}

void decoder_ToBuffer(void)
{
    // Fill buffer with the info of the mp3
    uint16_t bytesRead;

    uint8_t* dest = mp3FrameBuffer + bottomPosition;
    bytesRead = decoder_readFile(dest, (FRAME_BYTES - bottomPosition));
    // Update bottom pointer with the bytes read
    bottomPosition += bytesRead;
}


size_t decoder_readFile(void* buf, size_t count)
{
    size_t read;
    FRESULT fr;
    fr = f_read(mp3File, ((uint8_t*)buf), count, &read);
    if (fr == FR_OK)
        return read;
    return 0;
}


void decoder_readID3Tag(void)
{
    // checks if the file has ID3 Tag inside with the ID3 library
    if (has_ID3_tag(mp3File))
    {
        // if you are here it means that the file has ID3
        hasID3 = true;

        if (!read_ID3_info(TITLE_ID3, title, ID3_MAX_NUM_CHARS, mp3File))
            strcpy(title, DEFAULT_ID3);

        if (!read_ID3_info(ALBUM_ID3, album, ID3_MAX_NUM_CHARS, mp3File))
            strcpy(album, DEFAULT_ID3);

        if (!read_ID3_info(ARTIST_ID3, artist, ID3_MAX_NUM_CHARS, mp3File))
            strcpy(artist, DEFAULT_ID3);

        if (!read_ID3_info(YEAR_ID3, year, ID3_MAX_NUM_CHARS, mp3File))
            strcpy(year, DEFAULT_ID3);

        if (!read_ID3_info(TRACK_NUM_ID3, trackNum, ID3_MAX_NUM_CHARS, mp3File))
            strcpy(trackNum, DEFAULT_ID3);

        // here we get the size of the tag
        unsigned int tagSize = get_ID3_size(mp3File);
        
        // we moves the position according to the tagSize
        f_lseek(mp3File, tagSize);
        bytesRem -= tagSize;

    }
    else
    {
        // if you are here the mp3 file has not ID3 Tag
        f_rewind(mp3File);
    }
}