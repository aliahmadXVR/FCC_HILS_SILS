#include "stdafx.h"
#define Veronte_Def
#include "Veronte.h"

static char UDP_Send_Counter = 1;
extern struct tag_Servo	Servo;

void PIPE::Connect()
{
	HUB_Veronte.Initialize_UDP("Server");
	Veronte_HUB.Initialize_UDP("Client");
}

void PIPE::Closeall()
{
	HUB_Veronte.Closeall();
	Veronte_HUB.Closeall();
}


void PIPE::Received_Data()
{
	char Buff[1024]; 
	while( Cockpit.Terminate == 0)
	{
		
		int Received_Bytes = HUB_Veronte.UDP_Receive_Buffer(Buff, 1024, &Veronte_HUB_Sock, &Veronte_HUB_Addr);
		if (Received_Bytes == 0)
		{
			cout << "Error in Receiving data from Veronte" << endl;
		}
		
		//	cout << Buff << endl;
		Simulation.Veronte_Data_Rec_Counter++;
		Veronte.Rx_Status.Flags.Rx_Sync = 1;
		Decode_Data(Buff, Received_Bytes);

	}
}

void  PIPE::Decode_Data(char * Buff, int Rec_Bytes)
{

	char Str_char[100];
	
	if(Cockpit.Auto_Manual_Mode == 1)
	{
		if ( (*(Buff + 5) == 0x0B) &&  (*(Buff + 6) == 0x00) &&  (*(Buff + 7) == 0x00) &&  (*(Buff + 8) == 0x00))
		{
			Unpack_Bing_Endian(Buff, 9);
			Veronte.Elevator = Veronte_Receiving_Union.F_Temp * 10.0;
	
			Unpack_Bing_Endian(Buff, 13);
			Veronte.Aileron = Veronte_Receiving_Union.F_Temp * 10.0;

			Unpack_Bing_Endian(Buff, 17);
			Veronte.Rudder = Veronte_Receiving_Union.F_Temp * 10.0;

			Unpack_Bing_Endian(Buff, 25);
			Veronte.Flap = 0.0;//Veronte_Receiving_Union.F_Temp * 10.0;

			if (Rec_Bytes == 113)
			{

				Unpack_Bing_Endian(Buff, 81);
				Veronte.Throttle = Veronte_Receiving_Union.F_Temp;

			}
			Log_Data();
		//	cout << "E  "<< Servo.Elevator << " A  "<< Servo.Aileron<< " R  "<< Servo.Rudder<< " F  "<< Servo.Flap<< " T  "<< Servo.Throttle<< endl;
		}
	}	
}

void  PIPE::Transmit_Data()
{
	Encode_Data();
	Send_Data(Veronte.Data_Out, 221);
}

void  PIPE::Send_Data(char * Buff, int Length)
{
	if	( HUB_Veronte.UDP_Send_Buffer(Buff,Length, &HUB_Veronte_Sock, &HUB_Veronte_Addr) == 0 )
	{
		cout << "Error in sending data to Veronte" << endl;
	}

}

void  PIPE::Encode_Data()
{

	const int Dummy = 0xC479C000;
	const int IASTASHdr = 0x00000003;
	const int MachVVIHdr = 0x00000004;
	const int AngularVelHDR = 0x00000010;
	const int PitchRollHDR = 0x00000011;
	const int AOABetaHdr = 0x00000012;
	const int LatLongHdr = 0x00000014;

	
	/*
	JSBSIM.TAS = 99;
	JSBSIM.Ground_Speed_MPS = 100;
	
	JSBSIM.MachNumber = .7;
	JSBSIM.Hdot = 20.0;

	System_States.Rate.p_RPS = .66;
	System_States.Rate.q_RPS = .77;
	System_States.Rate.r_RPS = .88;

	System_States.Angle.Theta = .18;
	System_States.Angle.Phi = .22;
	System_States.Angle.Psi = .33;
	JSBSIM.Mag_Heading = .44;

	JSBSIM.AoA = 0.15;
	JSBSIM.Beta = 0.37;
	JSBSIM.Gama = 0.17;

	System_States.IMU_Position.Lat = .58;
	System_States.IMU_Position.Long = 1.26;
	System_States.IMU_Position.Alt = 1000;
	JSBSIM.HaGL = 700;

	System_States.Acceleration.u_MPS = 20;
	System_States.Acceleration.v_MPS = 30;
	System_States.Acceleration.w_MPS = 40;
	System_States.Velocity.u_MPS = 60;
	System_States.Velocity.u_MPS = 70;
	System_States.Velocity.u_MPS = 90;
	*/
	
	
	
	

	//Veronte_Sending_Union.UI_Temp =  0x44, 0x41, 0x54, 0x41, 0x40;
	// Data@
	Veronte.Data_Out[0] = 0x44;
	Veronte.Data_Out[1] = 0x41;
	Veronte.Data_Out[2] = 0x54;
	Veronte.Data_Out[3] = 0x41;
	Veronte.Data_Out[4] = 0x40;


	//--------------------------------IASTASHdr-----------------------------------

	Veronte_Sending_Union.UI_Temp = IASTASHdr;
	
	Pack_Big_Endian(&Veronte.Data_Out[5], 5);

	// True Speed
	Veronte_Sending_Union.F_Temp =JSBSIM.TAS_MPS;
	Pack_Big_Endian(&Veronte.Data_Out[9], 9);
	Pack_Big_Endian(&Veronte.Data_Out[13], 13);
	Pack_Big_Endian(&Veronte.Data_Out[17], 17);
	
	Veronte_Sending_Union.F_Temp = JSBSIM.Ground_Speed_MPS;
	Pack_Big_Endian(&Veronte.Data_Out[21], 21);
	
	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[25], 25);

	Veronte_Sending_Union.F_Temp = JSBSIM.TAS_MPS;
	Pack_Big_Endian(&Veronte.Data_Out[29], 29);
	Pack_Big_Endian(&Veronte.Data_Out[33], 33);
	Pack_Big_Endian(&Veronte.Data_Out[37], 37);
//cout << "9  "<< Veronte.Data_Out[9] << "10  "<< Veronte.Data_Out[10]<< "11  "<< Veronte.Data_Out[11]<< "12  "<<Veronte.Data_Out[12] <<endl;
	
//--------------------------------MachVVIHdr-----------------------------------

	Veronte_Sending_Union.UI_Temp = MachVVIHdr;
	Pack_Big_Endian(&Veronte.Data_Out[41], 41);

	// Mach No.
	Veronte_Sending_Union.F_Temp = JSBSIM.MachNumber;
	Pack_Big_Endian(&Veronte.Data_Out[45], 45);

	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[49], 49);

	Veronte_Sending_Union.F_Temp = JSBSIM.Hdot * 3.32;		// Vertical Velocity
	Pack_Big_Endian(&Veronte.Data_Out[53], 53);

	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[57], 57);

	Veronte_Sending_Union.F_Temp = System_States.Acceleration.w_MPS;	// Gvalue
	Pack_Big_Endian(&Veronte.Data_Out[61], 61);
	
	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[65], 65);
	Pack_Big_Endian(&Veronte.Data_Out[69], 69);
	Pack_Big_Endian(&Veronte.Data_Out[73], 73);

//--------------------------------AngularVelHDR-----------------------------------

	Veronte_Sending_Union.UI_Temp = AngularVelHDR;
	Pack_Big_Endian(&Veronte.Data_Out[77], 77);

	// Thetdot Speed
	Veronte_Sending_Union.F_Temp = System_States.Rate.q_RPS ;
	Pack_Big_Endian(&Veronte.Data_Out[81], 81);

	// phidot Speed
	Veronte_Sending_Union.F_Temp = System_States.Rate.p_RPS ;
	Pack_Big_Endian(&Veronte.Data_Out[85], 85);

	// psidot Speed
	Veronte_Sending_Union.F_Temp = System_States.Rate.r_RPS ;
	Pack_Big_Endian(&Veronte.Data_Out[89], 89);

	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[93], 93);
	Pack_Big_Endian(&Veronte.Data_Out[97], 97);
	Pack_Big_Endian(&Veronte.Data_Out[101], 101);
	Pack_Big_Endian(&Veronte.Data_Out[105], 105);
	Pack_Big_Endian(&Veronte.Data_Out[109], 109);
	

//--------------------------------PitchRollHDR-----------------------------------

	Veronte_Sending_Union.UI_Temp = PitchRollHDR;
	Pack_Big_Endian(&Veronte.Data_Out[113], 113);

	Veronte_Sending_Union.F_Temp = System_States.Angle.Theta * 57.29;
	Pack_Big_Endian(&Veronte.Data_Out[117], 117);

	Veronte_Sending_Union.F_Temp = System_States.Angle.Phi * 57.29;
	Pack_Big_Endian(&Veronte.Data_Out[121], 121);

	Veronte_Sending_Union.F_Temp = System_States.Angle.Psi * 57.29;
	Pack_Big_Endian(&Veronte.Data_Out[125], 125);

	JSBSIM.Mag_Heading = System_States.Angle.Psi  * 57.29 - (float)2.10672;
    
	if (JSBSIM.Mag_Heading < 0)	JSBSIM.Mag_Heading = 360.0 + JSBSIM.Mag_Heading;
	
	Veronte_Sending_Union.F_Temp = JSBSIM.Mag_Heading / 57.29;
	Pack_Big_Endian(&Veronte.Data_Out[129], 129);
	
	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[133], 133);
	Pack_Big_Endian(&Veronte.Data_Out[137], 137);
	Pack_Big_Endian(&Veronte.Data_Out[141], 141);
	Pack_Big_Endian(&Veronte.Data_Out[145], 145);


//--------------------------------AOABetaHdr-----------------------------------

	Veronte_Sending_Union.UI_Temp = AOABetaHdr;
	Pack_Big_Endian(&Veronte.Data_Out[149], 149);

	Veronte_Sending_Union.F_Temp = JSBSIM.AoA;
	Pack_Big_Endian(&Veronte.Data_Out[153], 153);

	Veronte_Sending_Union.F_Temp = JSBSIM.Beta;
	Pack_Big_Endian(&Veronte.Data_Out[157], 157);

	Veronte_Sending_Union.F_Temp = System_States.Angle.Psi;
	Pack_Big_Endian(&Veronte.Data_Out[161], 161);

	Veronte_Sending_Union.F_Temp = JSBSIM.Gama;	// flight path angle
	Pack_Big_Endian(&Veronte.Data_Out[165], 165);

//	Veronte_Sending_Union.UI_Temp = Dummy;
	Pack_Big_Endian(&Veronte.Data_Out[169], 169);
	Pack_Big_Endian(&Veronte.Data_Out[173], 173);
	Pack_Big_Endian(&Veronte.Data_Out[177], 177);

	Veronte_Sending_Union.F_Temp = JSBSIM.Beta;
	Pack_Big_Endian(&Veronte.Data_Out[181], 181);


//--------------------------------LatLongHdr-----------------------------------

	Veronte_Sending_Union.UI_Temp = LatLongHdr;
	Pack_Big_Endian(&Veronte.Data_Out[185], 185);

	Veronte_Sending_Union.F_Temp = System_States.IMU_Position.Lat * 57.29;
	Pack_Big_Endian(&Veronte.Data_Out[189], 189);

	Veronte_Sending_Union.F_Temp = System_States.IMU_Position.Long * 57.29;
	Pack_Big_Endian(&Veronte.Data_Out[193], 193);

	Veronte_Sending_Union.F_Temp = System_States.IMU_Position.Alt * 3.32;
	Pack_Big_Endian(&Veronte.Data_Out[197], 197);

	Veronte_Sending_Union.F_Temp = JSBSIM.HaGL * 3.28;	
	Pack_Big_Endian(&Veronte.Data_Out[201], 201);

	Veronte_Sending_Union.F_Temp = 0.0;
	Pack_Big_Endian(&Veronte.Data_Out[205], 205);

	Veronte_Sending_Union.F_Temp = System_States.IMU_Position.Alt + 500.0;
	Pack_Big_Endian(&Veronte.Data_Out[209], 209);

	Veronte_Sending_Union.F_Temp = 33.0;
	Pack_Big_Endian(&Veronte.Data_Out[213], 213);

	Veronte_Sending_Union.F_Temp = 71.0;
	Pack_Big_Endian(&Veronte.Data_Out[217], 217);


}



void PIPE::Log_Data()
{
	char Str_char[1024];
	sprintf_s(Str_char,"%d,%f,%d,%d,%f,%f,%f,%f\n",\
						\
						Simulation.Time,
						JSBSIM.Simulation_Time,
						Simulation.Veronte_Data_Rec_Counter,
						Simulation.JSB_Sim_Data_Rec_Counter,\
						\
						Veronte.Elevator,
						Veronte.Aileron,
						Veronte.Rudder,
						Veronte.Flap,\
						\
						Veronte.Throttle\
						);
	Veronte_Logg.Store_Buffer(&(In_System_Log_Veronte.My_File),Str_char);
}

void  PIPE::Pack_Little_Endian(char *Buff, unsigned int Index)
{
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[3];
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[2];
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[1];
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[0];
}

void  PIPE::Pack_Big_Endian(char *Buff, unsigned int Index)
{
	
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[0];
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[1];
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[2];
	Veronte.Data_Out[Index++] = Veronte_Sending_Union.UC_Temp_Arry[3];
}

void  PIPE::Unpack_Bing_Endian(char * Buff, int Index)
{
	Veronte_Receiving_Union.UC_Temp_Arry[0] = *(Buff + Index++);
	Veronte_Receiving_Union.UC_Temp_Arry[1] = *(Buff + Index++);
	Veronte_Receiving_Union.UC_Temp_Arry[2] = *(Buff + Index++);
	Veronte_Receiving_Union.UC_Temp_Arry[3] = *(Buff + Index++);
	
	
}



void PIPE::Initilalize_Veronte_Log()
{
	
	string Str =	"Hub_Sim_Time,"\
					"JSB_Simulation_Time,"\
					"Veronte_Data_Rec_Counter,"\
					"JSB_Sim_Data_Rec_Counter,"\

					"Veronte_Elevator_Cmd,"\
					"Veronte_Aileron_Cmd,"\
					"Veronte_Rudder_Cmd,"\
					"Veronte_Flaps_Cmd,"\

					"Veronte_Throttle_Cmd\n";


//	In_System_Log_Veronte.My_File.open("LogFile_Veronte_Data");
	Veronte_Logg.Open(&(In_System_Log_Veronte.My_File),"LogFile_Veronte_Data.csv");
	Veronte_Logg.Store_String(&(In_System_Log_Veronte.My_File),Str);
}

void PIPE::Close_Veronte_Log()
{
	Veronte_Logg.Close(&(In_System_Log_Veronte.My_File));
}
/*
void PIPE::Store_Buffer(char * Buff)
{
	Veronte_Logg.Store_Buffer(&(In_System_Log_Veronte.My_File),Buff);
}

void PIPE::Store_String(string Str)
{
	Veronte_Logg.Store_String(&(In_System_Log_Veronte.My_File),Str);
}
*/

