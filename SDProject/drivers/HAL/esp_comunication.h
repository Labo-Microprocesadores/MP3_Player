/***************************************************************************/ /**
  @file     esp_comunication.h
  @brief    Controlador de mesajer usando UART
  @author   Grupo 2
 ******************************************************************************/
#ifndef ESP_COMMUNICATION_H_
#define ESP_COMMUNICATION_H_

#include <stdbool.h>
#include <stdint.h>

void esp_Init(void);

void esp_Send(char code, char * msg, char len);
/*
bool esp_IsAnyMsg(void);

void esp_sendMsg(const char* msg, uint8_t cant);
uint8_t esp_getMsg(char* buffer, uint8_t max_cant);
*/
#endif /* ESP_COMMUNICATION_H_ */
