



#ifndef _AUDIO_PLAYER_H_
#define _AUDIO_PLAYER_H_

#include <stdint.h>


/*!
 * @brief Initialize the Audio Player.
 */
void AudioPlayer_Init(void);
void AudioPlayer_LoadSongInfo(uint16_t * firstSongFrame_, uint16_t songSize_, uint16_t sampleRate);
void AudioPlayer_UpdateSampleRate(uint16_t sampleRate);
void AudioPlayer_Play(void);
void AudioPlayer_Pause(void);
void AudioPlayer_Stop(void);

void AudioPlayer_DEMOMode(void);


#endif /* _AUDIO_PLAYER_H_ */
