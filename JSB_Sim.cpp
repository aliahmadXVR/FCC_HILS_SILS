#include "stdafx.h"
#define JSB_Sim_Def
#include "JSB_Sim.h"

void JSB_SIM::JSB_Sim_Receive_Data()
{
	char Buff[MAX_BUFF_Size];
	string Str;
	while( Cockpit.Terminate == 0)
	{
		JSBSIM.Rx_Status.Flags.Rx_Tel_Data = 0;	
		Str = JSB_HUB.TCP_Receive_String(Buff, &Server_Ser_Sock);
		if(strcmp(Str.c_str(),"\n") == 0)
		{
			cout << "No Data Reception from JSB Sim Telemetry Socket " << endl;
		}
		else
		{
			JSBSIM.Rx_Status.Flags.Rx_Tel_Data = 1;	
			JSBSIM.Rx_Status.Flags.Rx_Sync = 1;	
		}
		if(JSBSIM.Rx_Status.Flags.Rx_Tel_Data == 1)
		{
			//cout << Str;
			Simulation.JSB_Sim_Data_Rec_Counter++;

			if(Rec_Legends == 1)	JSB_Sim_Decode_Data(Buff);
			else
			{
				cout << Buff<< endl;
				Rec_Legends = 1;
			}
			
		}
	}
}

void JSB_SIM::JSB_Sim_Decode_Data(char *Buff)
{
	char * pch;
		
	//	Simulation Times
	pch = strtok (Buff, ",");
	JSBSIM.Simulation_Time = atof(pch);

	//	Linear Acceleration
	pch = strtok (NULL, ",");
	System_States.Acceleration.u_MPS = atof(pch) * 0.3048;
	pch = strtok (NULL, ",");
	System_States.Acceleration.v_MPS = atof(pch) * 0.3048;
	pch = strtok (NULL, ",");
	System_States.Acceleration.w_MPS = atof(pch) * 0.3048;

	//	Angular Velocities
	pch = strtok (NULL, ",");
	System_States.Rate.p_RPS = atof(pch);
	pch = strtok (NULL, ",");
	System_States.Rate.q_RPS = atof(pch);
	pch = strtok (NULL, ",");
	System_States.Rate.r_RPS = atof(pch);

	//	Linear Velocities
	pch = strtok (NULL, ",");
	System_States.Velocity.u_MPS = atof(pch) * 0.3048;
	pch = strtok (NULL, ",");
	System_States.Velocity.v_MPS = atof(pch) * 0.3048;
	pch = strtok (NULL, ",");
	System_States.Velocity.w_MPS = atof(pch) * 0.3048;

	//	Angles
	pch = strtok (NULL, ",");
	System_States.Angle.Phi = atof(pch);
	pch = strtok (NULL, ",");
	System_States.Angle.Theta = atof(pch);
	pch = strtok (NULL, ",");
	System_States.Angle.Psi = atof(pch);


	// System Posions
	pch = strtok (NULL, ",");
	System_States.IMU_Position.Lat = atof(pch);
	pch = strtok (NULL, ",");
	System_States.IMU_Position.Long = atof(pch);
	pch = strtok (NULL, ",");
	System_States.IMU_Position.Alt = atof(pch) * 0.3048;

	//Spare
	pch = strtok (NULL, ",");
	JSBSIM.Gama =  atof(pch);
	Estimated_Sensors.Gamma = JSBSIM.Gama; //Only added for Testing the controller. To be removed afterwards.
	pch = strtok (NULL, ",");
	JSBSIM.AoA  = atof(pch);
	Estimated_Sensors.Alpha = JSBSIM.AoA; //Only added for Testing the controller. To be removed afterwards.
	pch = strtok (NULL, ",");
	JSBSIM.HaGL  =  atof(pch) * 0.3048;

	pch = strtok (NULL, ",");
	JSBSIM.Mag_Heading  = atof(pch);
	Estimated_Sensors.Heading = JSBSIM.Mag_Heading;  //Only added for Testing the controller. To be removed afterwards.
	pch = strtok (NULL, ",");
	JSBSIM.Beta  = atof(pch);
	pch = strtok (NULL, ",");
	JSBSIM.MachNumber  =  atof(pch);

	pch = strtok (NULL, ",");
	JSBSIM.Hdot = atof(pch) * 0.3048;
	pch = strtok (NULL, ",");
	JSBSIM.TAS_MPS  = atof(pch) *0.5144;	// kts to meter per second
	Estimated_Sensors.TAS = JSBSIM.TAS_MPS; //Only added for Testing the controller. To be removed afterwards.
	pch = strtok (NULL, ",");
	JSBSIM.Ground_Speed_MPS  = atof(pch) * 0.3048;
	Estimated_Sensors.Ground_Speed_MPS = JSBSIM.Ground_Speed_MPS; //Only added for Testing the controller. To be removed afterwards.

	pch = strtok (NULL, ",");
	JSBSIM.Log_Var[9]  = atof(pch);
	pch = strtok (NULL, ",");
	JSBSIM.Log_Var[10]  = atof(pch);
	pch = strtok (NULL, ",");
	JSBSIM.Log_Var[11]  = atof(pch);

	pch = strtok (NULL, ",");
	JSBSIM.Log_Var[12]  = atof(pch);
	pch = strtok (NULL, ",\n");
	JSBSIM.Log_Var[13]  = atof(pch);

	Log_Data();
	
}

string JSB_SIM::JSB_Sim_Encode_Data()
{	
	char JSB_SIM_Cmd_Str[100];
	std::ostringstream ss;
	
	// Normalize Data according to JSB Sim input

	JSBSIM.da_Cmd_Norm = (float) Servo.Aileron / 10.0;
	JSBSIM.de_Cmd_Norm = (float) Servo.Elevator / 15.0;
	JSBSIM.dr_Cmd_Norm = (float) Servo.Rudder / 15.0;
	JSBSIM.dt_Cmd_Norm = (float) Servo.Throttle / 1.0;
	JSBSIM.df_Cmd_Norm = (float) Servo.Flap / 10.0;

/*	JSBSIM.da_Cmd_Norm = 0.15465465;
	JSBSIM.de_Cmd_Norm = 0.25546546; 
	JSBSIM.dr_Cmd_Norm = 0.35984654;
	JSBSIM.dt_Cmd_Norm = 0.7376465;
	JSBSIM.df_Cmd_Norm = 0.05154987;*/

//	sprintf_s(JSB_SIM_Cmd_Str,"set, %.2f, %.2f, %.2f, %.2f, %.2f\n", JSBSIM.da_Cmd_Norm, JSBSIM.de_Cmd_Norm, JSBSIM.dr_Cmd_Norm, JSBSIM.dt_Cmd_Norm, JSBSIM.df_Cmd_Norm );
	sprintf_s(JSB_SIM_Cmd_Str,"set, %.2f, %.2f, %.2f, %.2f\n", JSBSIM.dt_Cmd_Norm, JSBSIM.de_Cmd_Norm, JSBSIM.da_Cmd_Norm, JSBSIM.df_Cmd_Norm );

	ss << JSB_SIM_Cmd_Str;
	std::string s(ss.str());

//	cout << s;
	return s;
	
}

void JSB_SIM::JSB_Sim_Send_Data(string Str)
{
	if	(	HUB_JSB.TCP_Send_String(Str, &Client_Cli_Sock) == 0)
	{
		cout << "Error in sending data to JSB Sim" << endl;
	}
}


void JSB_SIM::JSB_Sim_Connect()
{
	JSB_HUB.Initialize_Socket("TCP", "Server");
	HUB_JSB.Initialize_Socket("TCP", "Client");	

}

void JSB_SIM::JSB_SIM_Closeall()
{
	JSB_HUB.Closeall();
	HUB_JSB.Closeall();
}


double JSB_SIM::Stream_Float(char *Src, char C, int Index) 
{

	// each data will be 13 charater including ';'
	int i = 0;
	char Temp[13]; 
	int Index_S = Index - 2;

	while( (Src[Index_S] != ' ') && (Src[Index_S] != ',') ) Index_S--;
	Index_S++;
	
	while (Index_S <= (Index - 2))
	{
		Temp[i++] = Src[Index_S++];
	}
	 
    return atof(Temp);
}


// this function is used in feedback only
void JSB_SIM::JSB_Sim_Transmit_Data()
{
	
	string Str = JSB_Sim_Encode_Data();
	JSB_Sim_Send_Data(Str);
	
	// Used only in acknowledge only
	//JSBSIM.Tx_Status.Flags.TX_Enable = 1;
	//while(JSBSIM.Tx_Status.Flags.TX_Enable == 1);
	
}


void JSB_SIM::Initilalize_JSB_SIM_Log()
{
	string Str =	"Hub_Sim_Time,"\
					"JSBSIM_Simulation_Time,"\
					"Veronte_Data_Rec_Counter,"\
					"JSB_Sim_Data_Rec_Counter,"\
					
					"x_Acc_Mps,"\
					"y_Acc_Mps,"\
					"z_Acc_Mps,"\
					
					"Roll_Rate_Rps,"\
					"Pitch_Rate_Rps,"\
					"Yaw_Rate_Rps,"\

					"u_Mps,"\
					"v_Mps,"\
					"w_Mps,"\

					"Phi_Rad,"\
					"Theta_Rad,"\
					"Psi_Rad,"\

					"IMU_Lat_Rad,"\
					"IMU_Long_rad,"\
					"IMU_Alt,"\

					"IMU_AGL,"\
					"MachNumber,"\
					"Hdot_Mps,"\
					"TAS_Kts,"\
					"SoG_Mps\n";

	JSB_SIM_Logg.Open(&(In_System_Log_JSB_SIM.My_File),"LogFile_JSB_SIM_Data.csv");
	JSB_SIM_Logg.Store_String(&(In_System_Log_JSB_SIM.My_File),Str);
}

void JSB_SIM::Close_JSB_SIM_Log()
{
	JSB_SIM_Logg.Close(&(In_System_Log_JSB_SIM.My_File));
}


void JSB_SIM::Log_Data()
{
	char Str_char[1024];
	
	sprintf_s(Str_char,"%d,%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",\

						\
						Simulation.Time,
						JSBSIM.Simulation_Time,
						Simulation.Veronte_Data_Rec_Counter,
						Simulation.JSB_Sim_Data_Rec_Counter,\
						\
						System_States.Acceleration.u_MPS,
						System_States.Acceleration.v_MPS,
						System_States.Acceleration.w_MPS,
						System_States.Rate.p_RPS * 57.29,\
						\
						System_States.Rate.q_RPS * 57.29,
						System_States.Rate.r_RPS * 57.29,
						System_States.Velocity.u_MPS,
						System_States.Velocity.v_MPS,\
						\
						System_States.Velocity.w_MPS,
						System_States.Angle.Phi * 57.29,
						System_States.Angle.Theta * 57.29,
						System_States.Angle.Psi * 57.29,\
						\
						System_States.IMU_Position.Lat * 57.29,
						System_States.IMU_Position.Long * 57.29,
						System_States.IMU_Position.Alt * 3.32,\
						JSBSIM.HaGL * 3.32,\
						\
						JSBSIM.MachNumber,
						JSBSIM.Hdot * 3.32,
						JSBSIM.TAS_MPS,
						JSBSIM.Ground_Speed_MPS,\

						JSBSIM.de_Cmd_Norm,
						JSBSIM.da_Cmd_Norm,
						JSBSIM.df_Cmd_Norm,\
						\
						JSBSIM.dt_Cmd_Norm
						);






						



	JSB_SIM_Logg.Store_Buffer(&(In_System_Log_JSB_SIM.My_File),Str_char);

}





string JSB_SIM::JSB_Sim_Encode_Data_Individual_Cmd(int Data_Index)
{	
	float myFloat = 2.5;
	std::ostringstream ss;
	char Val[20];

	sprintf_s(Val,"%.2f", JSBSIM.Out_Data[Data_Index]);
	ss << JSBSIM.Out_Cmd[Data_Index] << Val <<"\n";
	std::string s(ss.str());
//	cout << s;
	return s;
}


void JSB_SIM::JSB_Sim_Transmit_Data_Feedback()
{
	unsigned int Flag_Index =1;
	string Temp_Str;
	unsigned int Time_Out;
	
	while(true)
	{
		while(JSBSIM.Tx_Status.Flags.TX_Enable == 0);

		for (int Loop = 0; Loop < Max_No_Tx_Data; )
		{
			Time_Out = 0;
			JSBSIM.Tx_Status.Flags.Rec_Ack = 0;
			JSBSIM.Tx_Status.Flags.TimeOut = 0;
			
			Temp_Str = JSB_Sim_Encode_Data_Individual_Cmd(Loop);
//			cout<< "Sending CMd is " << Temp_Str ;
			JSB_Sim_Send_Data(Temp_Str);
			
			JSBSIM.Tx_Status.Flags.Rec_Enable = 1;

			// wait for Acknowledge and/or Err and/or Timeout 
			while((JSBSIM.Tx_Status.Flags.Rec_Err == 0) && (JSBSIM.Tx_Status.Flags.TimeOut == 0) && (JSBSIM.Tx_Status.Flags.Rec_Ack == 0))
			{
				Time_Out++;
				if(Time_Out >= 16777216)	JSBSIM.Tx_Status.Flags.TimeOut = 1;
			}	

			if(JSBSIM.Tx_Status.Flags.Rec_Ack == 1)
			{
				JSBSIM.Tx_Status.Byte &= (~(1<<Loop));
				Loop++;
			}
		}
		JSBSIM.Tx_Status.Flags.TX_Enable = 0;
	}
}





void JSB_SIM::JSB_Sim_Rec_Ack()
{
	string Str;
	
	char Buff[MAX_BUFF_Size];
	while( Cockpit.Terminate == 0)
	{
		while(JSBSIM.Tx_Status.Flags.Rec_Enable == 0);
		
		JSBSIM.Tx_Status.Flags.Rec_Enable = 0;
		JSBSIM.Tx_Status.Flags.Rec_Err = 0;

		Str = JSB_HUB.TCP_Receive_String(Buff,&Client_Cli_Sock);
//		cout << "Received Ack is " << Str;
		if(strcmp(Str.c_str(),"\n") == 0)
		{
			cout << "No Data Reception Acknowledgement from JSB Sim " << endl;
			JSBSIM.Tx_Status.Flags.Rec_Err = 1;
		}

		if(strcmp(Str.c_str(),"set successful\n") != 0)
		{
			JSBSIM.Tx_Status.Flags.Rec_Err = 1;
			JSBSIM.Tx_Status.Flags.Rec_Ack = 0;
		}
		else
		{
			JSBSIM.Tx_Status.Flags.Rec_Err = 0;
			JSBSIM.Tx_Status.Flags.Rec_Ack = 1;
		}
	}
}

