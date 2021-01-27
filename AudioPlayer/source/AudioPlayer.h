



#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum {AP_NO_ERROR, AP_ERROR_BB_NOT_FREE} audioPlayerError;
/*!
 * @brief Initialize the Audio Player.
 */
void AudioPlayer_Init(void);
void AudioPlayer_LoadSongInfo(uint16_t * firstSongFrame, uint16_t * secondSongFrame, uint16_t frameSize_, uint16_t sampleRate);
void AudioPlayer_UpdateSampleRate(uint16_t sampleRate);
bool AudioPlayer_IsBackBufferFree(void);
audioPlayerError AudioPlayer_UpdateBackBuffer(uint16_t * newBackBuffer);
void AudioPlayer_Play(void);
void AudioPlayer_Pause(void);
void AudioPlayer_Stop(void);

void AudioPlayer_DEMOMode(void);


#endif /* _AUDIO_PLAYER_H_ */
