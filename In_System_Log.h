#ifndef In_System_Log_Inc
#define	In_System_Log_Inc

#include "Includes.h"
#include "Simulation_Structure.h"


class System_Logging 
{
public:
	void Close(ofstream *File_Handler);
	void Open(ofstream  *File_Handler, string Str);
	void Store_Buffer(ofstream *File_Handler, char* Buff);
	void Store_String(ofstream *File_Handler, string Str);
};

#endif


#ifdef	In_System_Log_Def

extern System_Logging JSB_Sim_Log;
extern System_Logging Simulation_Log;

#endif
