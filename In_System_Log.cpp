#include "stdafx.h"
#define In_System_Log_Def
#include "In_System_Log.h"


void System_Logging::Close(ofstream *File_Handler)
{
	File_Handler->close();
}
void System_Logging::Open(ofstream  *File_Handler, string Str)
{
	File_Handler->open(Str);
}
void System_Logging::Store_Buffer(ofstream *File_Handler, char* Buff)
{
	unsigned int Index = 0;
	std::ostringstream ss;
	do
	{
		if(Index < 1024)	ss<< Buff[Index];
		else	break;
	}while(Buff[Index++] != 0x0a);

	std::string s(ss.str());

	*File_Handler <<  s; 
}


void System_Logging::Store_String(ofstream *File_Handler, string Str)
{
	*File_Handler <<  Str; 
}