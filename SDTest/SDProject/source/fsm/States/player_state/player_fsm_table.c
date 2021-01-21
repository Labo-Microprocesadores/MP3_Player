#include <fsm/States/player_state/player_fsm_table.h>
#include <stdio.h>
#include "../../fsm.h"
#include "../../../queue.h"
#include "sub_states/play_state.h"
#include "sub_states/pause_state.h"


/*Foward Declarations*/

extern STATE play[];
extern STATE pause[];

static void do_nothing(void);

/*** tablas de estado ***/

/*** Play ***/
STATE play[]=
{
    {PRESS_EV, 						pause, 					pause_Pause},
	{LKP_EV, 						pause, 					pause_Pause},
	{EFF_EV, 						pause, 					pause_changeEffects},
	{FIN_TABLA, 					play, 					do_nothing}
};

/*** Pause ***/

STATE pause[]=
{
	{PRESS_EV, 						play, 					play_initState},
	{LKP_EV, 						play, 					play_initState},
	{FIN_TABLA,						pause,					do_nothing},
};




//========interfaz=================


STATE *subFSM_GetInitState(void)
{
	return(play);
}

///=========Rutinas de accion===============
void subFSM_StartInitState()
{
	play_initState();
}


/*Dummy function*/
static void do_nothing(void)
{

}
