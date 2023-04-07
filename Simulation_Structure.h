#ifndef	Simulation_Structure_Inc
#define	Simulation_Structure_Inc

// Interface Structure..............
#include <string>
#include <fstream>
#include "Includes.h"

using namespace std;

//OK
//----JSB-Sim Inteface----------
struct tag_JSBSIM
{
	float * Out_Data[10];
	string Out_Cmd[10];
	float * In_Data[20];
	string In_Cmd[20];
	
	float da_Cmd_Norm;
	float de_Cmd_Norm;
	float dr_Cmd_Norm;
	float dt_Cmd_Norm;
	float df_Cmd_Norm;

	float Gama;
	float AoA;
	float HaGL;

	float Mag_Heading;
	float Beta;

	float MachNumber;
	float Hdot;
	float TAS_MPS;
	float Ground_Speed_MPS;


	float Simulation_Time;
	float Log_Var[20];

	
	union
	{
		unsigned int Byte;
		struct 
		{
			unsigned int TX_Enable : 1;
			unsigned int Rec_Enable : 1;
			unsigned int da_Cmd : 1;
			unsigned int de_Cmd : 1;
			unsigned int dr_Cmd : 1;
			unsigned int dt_Cmd : 1;
			unsigned int df_Cmd : 1;
			unsigned int TimeOut : 1;
			unsigned int Rec_Ack : 1;
			unsigned int Rec_Err : 1;
		}Flags;
	}Tx_Status;
	
	union
	{
		unsigned int Byte;
		struct 
		{
			unsigned int Rx_Tel_Data : 1;
			unsigned int Rx_Sync : 1;
		}Flags;
	}Rx_Status;
};


struct tag_In_System_Log
{
	ofstream My_File;	//	used to open exsisting file

	HANDLE	HLog_File;
	DWORD	dBytesSent;

};


struct tag_Veronte
{
	char Data_Out[250];
	float Simulation_Time;
	float Elevator;
	float Rudder;
	float Aileron;
	float Throttle;
	float Flap;
	
	union
	{
		unsigned int Byte;
		struct 
		{
			unsigned int TX_Enable : 1;
		}Flags;
	}Tx_Status;
	union
	{
		unsigned int Byte;
		struct 
		{
			unsigned int Rx_Sync : 1;
		}Flags;
	}Rx_Status;
};




// Joystic
struct tag_Cockpit
{	
	float Elevator;
	float Rudder;
	float Aileron;
	float Throttle;
	float Flap;
	int Auto_Manual_Mode;
	int Terminate;

	struct
	{	
		float Elevator;
		float Rudder;
		float Aileron;
		float Throttle;
		float Flap;
		struct
		{
			float Elevator;
			float Rudder;
			float Aileron;
			float Throttle;
			float Flap;
		}Trim;
	} Keyboard;
	struct
	{
		float Elevator;
		float Rudder;
		float Aileron;
		float Throttle;
		float Flap;
		struct
		{
			float Elevator;
			float Rudder;
			float Aileron;
			float Throttle;
			float Flap;
		}Trim;
	
	}Joystic;

};


struct tag_Simulation
{
	unsigned int Time;
	unsigned int Veronte_Data_Rec_Counter;
	unsigned int JSB_Sim_Data_Rec_Counter;
};






#endif
