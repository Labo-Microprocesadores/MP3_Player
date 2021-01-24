/***************************************************************************/ /**
  @file     fsm_Table.c
  @brief    FSM Table
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <fsm/States/effects_state.h>
#include <stdio.h>
#include "fsm.h"
#include "fsm_table.h"
#include "States/idle_state.h"
#include "States/file_selection_state.h"
#include "States/player_state.h"
#include "States/effects_state.h"
#include "queue.h"


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/
static void do_nothing(void);

/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/
/*Foward Declarations*/

extern STATE idle[];
extern STATE effects[];
extern STATE player[];
extern STATE file_selection[];


/*** tablas de estado ***/

/*** Idle State ***/

 STATE idle[]=
{
	{PRESS_EV,				idle, 					Idle_OnUserInteraction},
	{LKP_EV,				idle, 					Idle_OnUserInteraction},
	{SD_IN_EV, 				file_selection, 		FileSelection_InitState},
  	{FIN_TABLA, 			idle, 					do_nothing}
};

/*** Effects State ***/

STATE effects[] =
{
	{PRESS_EV,				effects, 				NULL},
	{LKP_EV, 				effects, 				NULL},
	{TIMEOUT_EV, 			idle, 					Idle_InitState},
	{CHANGE_MODE_EV,		player,					Player_InitState},
	{SD_OUT_EV, 			idle, 					Idle_InitState},
	{FIN_TABLA, 			effects, 				do_nothing}
};


/*** File Selection State ***/
STATE file_selection[] =
{
	{SD_OUT_EV, 			idle, 					Idle_InitState},
	{TIMEOUT_EV,			idle,					Idle_InitState},
	{PRESS_EV,				file_selection, 		NULL},
	{LKP_EV, 				file_selection, 		NULL},
	{CHANGE_MODE_EV, 		effects, 				Effects_InitState},
	{FIN_TABLA, 			file_selection, 		do_nothing}
};

/*** Player State ***/
STATE player[] =
{
	{PRESS_EV,				player, 				NULL},
	{LKP_EV, 				player, 				NULL},
	{CHANGE_MODE_EV, 		file_selection, 		FileSelection_InitState},
	{SD_OUT_EV, 			idle, 					Idle_InitState},
	{TIMEOUT_EV,			idle,	 				Idle_InitState},
	{FIN_TABLA, 			player, 				do_nothing}
};


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

//========interfaz=================
STATE *FSM_GetInitState(void)
{
	 return(idle);
}


///=========Rutinas de accion===============
void FSM_StartInitState()
{
}

/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/
/*Dummy function*/
static void do_nothing(void)
{
	//take some time off, relax, and KEEP WORKING ////you lazy ass ALU
}
