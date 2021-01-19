#include <fsm/States/player_state/player_fsm_table.h>
#include <stdio.h>
#include "../../fsm.h"
#include "../../../queue.h"
#include "sub_states/play_state.h"
#include "sub_states/pause_state.h"


/*Foward Declarations*/

extern STATE play[];
extern STATE pause[];

// prototipos
static void do_nothing(void);

/*** tablas de estado ***/

/*** Play ***/
STATE play[]=
{
    {PRESS_EV, 						pause, 					NULL},
	{LKP_EV, 						pause, 					NULL},
	{EFF_EV, 						pause, 					NULL},
	{FIN_TABLA, 					play, 					do_nothing}
};

/*** Pause ***/

STATE pause[]=
{
	{PRESS_EV, 						play, 					NULL},
	{LKP_EV, 						play, 					NULL},
	{FIN_TABLA,						pause,					do_nothing},
};




//========interfaz=================


STATE *subFSM_GetInitState(void) // cambiar nombre
{
	return(play);
}

///=========Rutinas de accion===============
void subFSM_StartInitState() // cambiar nombre
{
	play_initState();
}


/*Dummy function*/
static void do_nothing(void)
{

}
