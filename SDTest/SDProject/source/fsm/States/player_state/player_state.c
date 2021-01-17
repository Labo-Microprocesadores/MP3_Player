/***************************************************************************/ /**
  @file     add_user.c
  @brief    add user state functions
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <fsm/States/player_state/player_fsm_table.h>
#include <fsm/States/player_state/player_state.h>
#include <stdbool.h>
#include "queue.h"
/*******************************************************************************
 * GLOBAL VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/
static STATE *currentState;

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 **********************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
void player_initFSM(void)
{
    currentState = subFSM_GetInitState();
    subFSM_StartInitState();
}


void player_onLKP(void)
{
    currentState = fsm(currentState, LKP_EV);
}
void player_onPress(void)
{
    currentState = fsm(currentState, PRESS_EV);
}

void player_onStorageOut(void)
{
    currentState = fsm(currentState, ST_OUT_EV);
}

void player_onTimeOut(void)
{
    currentState = fsm(currentState, TIMEOUT_EV);
}
