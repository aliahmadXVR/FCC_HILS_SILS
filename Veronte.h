#ifndef Veronte_Inc
#define Verotne_Inc

#include "Includes.h"
#include "AutoPilot/Structure.h"
#include "Simulation_Structure.h"
#include "Socket.h"
#include "In_System_Log.h"

class PIPE 
{
public:
	void Connect();
	void Closeall();
	void Received_Data();
	void Decode_Data(char * Buff, int Rec_Bytes);
	void Transmit_Data();
	void Encode_Data();
	void Send_Data(char * Buff, int Length);
	void Log_Data();
	void Pack_Little_Endian(char *Buff, unsigned int Index);
	void Pack_Big_Endian(char *Buff, unsigned int Index);
	void Unpack_Bing_Endian(char * Buff, int Rec_Bytes);
	void Initilalize_Veronte_Log();
	void Close_Veronte_Log();
	void Store_Buffer(char * Buff);
	void Store_String(string Str);
};


#endif


#ifdef Veronte_Def


HUB_Socket		HUB_Veronte;
HUB_Socket		Veronte_HUB;
System_Logging	Veronte_Logg;

struct tag_Veronte			Veronte;
struct tag_In_System_Log	In_System_Log_Veronte;

union tag_Temp_Union	Veronte_Sending_Union;
union tag_Temp_Union	Veronte_Receiving_Union;

extern SOCKET	Veronte_HUB_Sock;		
extern SOCKET	HUB_Veronte_Sock;		

extern sockaddr_in	Veronte_HUB_Addr;		
extern sockaddr_in	HUB_Veronte_Addr;		

extern struct tag_JSBSIM		JSBSIM;
extern struct tag_Simulation	Simulation;
//extern struct tag_System_States System_States;
extern struct tag_Cockpit		Cockpit;

#endif
