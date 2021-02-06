/***************************************************************************/ /**
  @file     audio_manager.c
  @brief    Audio manager, to wrap file related function and decoding stuff
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

#ifndef AUDIO_MANAGER_AUDIO_MANAGER_H_
#define AUDIO_MANAGER_AUDIO_MANAGER_H_

void Audio_init(void);

void Audio_nextFile(void);

void Audio_prevFile(void);

void Audio_selectFile(void);

char * Audio_getCurrentName(void);

char * Audio_getArtist(void);

char * Audio_getAlbum(void);

char * Audio_getYear(void);

void Audio_updateBuffer(void);

void Audio_play(void);

void Audio_pause(void);

void Audio_stop(void);

void Audio_IncVolume(void);

void Audio_DecVolume(void);

char Audio_getVolume(void);

#endif /* AUDIO_MANAGER_AUDIO_MANAGER_H_ */
