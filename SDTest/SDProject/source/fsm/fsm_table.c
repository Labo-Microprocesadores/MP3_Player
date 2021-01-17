/***************************************************************************/ /**
  @file     fsm_Table.c
  @brief    FSM Table
  @author   Grupo 2 - Lab de Micros
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/
#include <stdio.h>
#include "fsm.h"
#include "fsm_table.h"

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
extern STATE main_menu[];
extern STATE main_effects[];
extern STATE storage_read[];
extern STATE player[];
extern STATE player_effects[];
extern STATE file_selection[];


/*** tablas de estado ***/

/*** Idle State ***/

 STATE idle[]=
{
	{START_EV, 				main_menu, 				NULL},
	{ST_IN_EV, 				storage_read, 			NULL},
  	{FIN_TABLA, 			idle, 					do_nothing}
};


/*** Main Menu State ***/

STATE main_menu[]=
{
	{PRESS_EV,				main_menu, 				NULL},
	{LKP_EV,				main_menu, 				NULL},
	{TIMEOUT_EV,			idle, 					NULL},
	{EFF_EV, 				main_effects, 			NULL},
	{ST_IN_EV, 				storage_read, 			NULL},
	{FIN_TABLA,				main_menu,				do_nothing},
};

/*** Main Effects State ***/

STATE main_effects[] =
{
	{PRESS_EV,				main_effects, 			NULL},
	{LKP_EV, 				main_effects, 			NULL},
	{EFF_SELECTED_EV,		main_menu, 				NULL},
	{TIMEOUT_EV, 			idle, 					NULL},
	{FIN_TABLA, 			main_effects, 			do_nothing}
};

/*** Storage Read State ***/

STATE storage_read[] =
{
	{ST_FAIL_EV, 			main_menu, 				NULL},
	{ST_OUT_EV, 			main_menu, 				NULL},
	{ST_OK_EV, 				file_selection, 		NULL},
	{FIN_TABLA, 			storage_read, 			do_nothing}
};

/*** File Selection State ***/
STATE file_selection[] =
{
	{ST_OUT_EV, 			main_menu, 				NULL},
	{TIMEOUT_EV,			idle,					NULL},
	{PRESS_EV,				file_selection, 		NULL},
	{LKP_EV, 				file_selection, 		NULL},
	{PLAY_EV, 				player, 				NULL},
	{FIN_TABLA, 			file_selection, 		do_nothing}
};

/*** Player State ***/
STATE player[] =
{
	{PRESS_EV,				player, 				NULL},
	{LKP_EV, 				player, 				NULL},
	{ST_OUT_EV, 			main_menu, 				NULL},
	{CHANGE_FILE_EV,		file_selection, 		NULL},
	{EFF_EV, 				player_effects, 		NULL},
	{FIN_TABLA, 			player, 				do_nothing}
};
/*** Player Effects State***/
STATE player_effects[] =
{	
	{PRESS_EV, 				player_effects, 		NULL},
	{LKP_EV, 				player_effects, 		NULL},
	{TIMEOUT_EV,			player, 				NULL},
	{EFF_SELECTED_EV, 		player, 				NULL},
	{ST_OUT_EV, 			main_menu, 				NULL},
	{FIN_TABLA, 			player_effects, 		do_nothing}
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
