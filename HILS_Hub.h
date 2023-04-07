#ifndef HILS_Hub_Inc
#define HILS_Hub_Inc

#include "Includes.h"
#include "AutoPilot/Structure.h"
#include "Simulation_Structure.h"

#include "JSB_Sim.h"
#include "Veronte.h"
#include "Cockpit.h"



#define HILS
#define SILS
//#define FCC
#define Veronte_FCC
/*
#ifdef SILS

#ifdef	FCC
#undef Veronte

#else if Veronte
#undef FCC
#endif

//#define Veronte
#define JSB_Sim
//#define FCC
//#define GPS


#else if HILS
	#define JSB_Sim
#endif
*/



#endif


#ifdef	HILS_Hub_Def

void HUB_Main_Loop();
void Initialize_Variable();
void HUB_Main_Initialization();
void HUB_Main_Loop(void * Dummy);
void JSB_Sim_Send_Cmd_Thread(void * Dummy);
void JSB_Sim_Rec_Ack_Thread(void * Dummy);
void JSB_Sim_Rec_Telemetry_Thread(void * Dummy);
void JSB_Sim_Cockpit_Control_Thread(void * Dummy);
void Veronte_Receive_Data_Thread(void * Dummy);
string Sstream_String (char * Buffer);
void Initilalize_HILS_HUB_Log();
void Close_HILS_HUB_Log();
void Log_Data();

/*----
External Definations for the Controller Files
----*/
extern "C"
{
	#include "AutoPilot\Structure.h"
	void call_flight_control(void);
	struct	tag_Guidance		Guidance;
	struct	tag_Control			Control;
	struct	tag_System_States    System_States;
	struct	tag_Servo			Servo;
	struct	tag_Estimated_Sensors	Estimated_Sensors;
}
/*----------*/

JSB_SIM			OFDM;
HILS_Cockpit	Cockpit_HILS;
PIPE			FCC_Veronte;
System_Logging	HILS_HUB_Logg;

struct tag_Simulation		Simulation;
struct tag_In_System_Log	In_System_Log_HILS_HUB;

extern struct tag_Cockpit	Cockpit;
extern struct tag_JSBSIM	JSBSIM;
extern struct tag_Veronte	Veronte;
//extern struct tag_System_States	System_States;

#endif

