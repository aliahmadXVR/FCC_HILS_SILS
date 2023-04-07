#ifndef JSB_Sim_Inc
#define	JSB_Sim_Inc

#include "AutoPilot/Structure.h"
#include "Simulation_Structure.h"
#include "Socket.h"
#include "In_System_Log.h"

#define Max_No_Tx_Data	4


class JSB_SIM 
{
	public:
	
	void JSB_Sim_Receive_Data();
	void JSB_Sim_Decode_Data(char *Buff);
	string JSB_Sim_Encode_Data();
	void JSB_Sim_Send_Data(string Str);
	void JSB_Sim_Transmit_Data();
	void JSB_Sim_Push_Data();

	void JSB_Sim_Transmit_Data_Feedback();
	void JSB_Sim_Rec_Ack();
	void JSB_Sim_Connect();
	void JSB_SIM_Closeall();
	void Initilalize_JSB_SIM_Log();
	void Close_JSB_SIM_Log();
	void Log_Data();

	double Stream_Float(char *Src, char C, int Index) ;
	string JSB_Sim_Encode_Data_Individual_Cmd(int Data_Index);



};

#endif

#ifdef	JSB_Sim_Def

static char Rec_Legends = 0;

HUB_Socket JSB_HUB;
HUB_Socket HUB_JSB;
System_Logging	JSB_SIM_Logg;

extern int Client_Ser_Port;
extern int Client_Cli_Port;

struct tag_In_System_Log	In_System_Log_JSB_SIM;
struct tag_JSBSIM			JSBSIM;
//extern struct tag_System_States	System_States;

extern struct tag_Auto_Pilot	Auto_Pilot;
extern struct tag_Servo			Servo;
extern struct tag_Simulation	Simulation;
extern struct tag_Cockpit		Cockpit;

extern SOCKET Server_Listen_Socket;		// for Server Side
extern SOCKET Server_Ser_Sock;				// for Server Side
extern SOCKET Server_Cli_Sock;				// for Server Side

extern sockaddr_in Server_Ser_Addr;		// for Server Side
extern sockaddr_in Server_Cli_Addr;		// for Server Side

extern SOCKET Client_Ser_Sock;				// for client Side
extern SOCKET Client_Cli_Sock;				// for client Side

extern sockaddr_in Client_Ser_Addr;		// for client Side
extern sockaddr_in Client_Cli_Addr;		// for client Side

#endif

