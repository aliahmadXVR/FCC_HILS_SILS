#include "stdafx.h"
#define HILS_Hub_Def
#include "HILS_Hub.h"

void main()
{
	HUB_Main_Initialization();
	
	while( Cockpit.Terminate == 0);
	
	
	OFDM.JSB_SIM_Closeall();
	FCC_Veronte.Closeall();

	FCC_Veronte.Close_Veronte_Log();
	OFDM.Close_JSB_SIM_Log();
	Close_HILS_HUB_Log();

}

void HUB_Main_Initialization()
{
	
	//	Initialize Variables
	Initialize_Variable();

	// Initialize Veronte and JSB_SIM Log
	FCC_Veronte.Initilalize_Veronte_Log();
	OFDM.Initilalize_JSB_SIM_Log();
	Initilalize_HILS_HUB_Log();

	//	Create Socket for Communication
	OFDM.JSB_Sim_Connect();
	

#ifdef Veronte_FCC
//	FCC_Veronte.Connect();
#endif
	//Initialize Serial Communications

#ifdef FCC

#ifdef GPS

#endif

#endif

	//Initialize Thread
	_beginthread(HUB_Main_Loop,0,NULL);	
	_beginthread(JSB_Sim_Rec_Telemetry_Thread,0,NULL);
	
#ifdef Veronte_FCC
//	_beginthread(Veronte_Receive_Data_Thread,0,NULL);
#endif
	
	_beginthread(JSB_Sim_Cockpit_Control_Thread,0,NULL);	
	
/* only use when run in cmd acknowledge*/	
//	_beginthread(JSB_Sim_Send_Cmd_Thread,0,NULL);	
//	_beginthread(JSB_Sim_Rec_Ack_Thread,0,NULL);

}

void HUB_Main_Loop(void * Dummy)
{
	char Str_char[100];
	
	while(true)
	{
		// Syn with real-time system
		
		while( JSBSIM.Rx_Status.Flags.Rx_Sync == 0 );
		JSBSIM.Rx_Status.Flags.Rx_Sync = 0;	
		
//		while( Veronte.Rx_Status.Flags.Rx_Sync == 0 );
//		Veronte.Rx_Status.Flags.Rx_Sync = 0;
		Simulation.Time++;

		// Receive Serial Data
		// Decode Serial Data

		// Receive Socket Data
		// Decode Socket Data

		// Check for AutoPilot
		if(Cockpit.Auto_Manual_Mode == 0)
		{
			Control.Control_Active = 0; //This variable indicates that manual mode is active. (For Logging Purpose)
			Servo.Aileron	= Cockpit.Aileron;
			Servo.Elevator	= Cockpit.Elevator;
			Servo.Flap		= Cockpit.Flap;
			Servo.Rudder	= Cockpit.Rudder;
			Servo.Throttle	= Cockpit.Throttle;
		//	printf("set, %.2f, %.2f, %.2f, %.2f\n", Servo.Aileron, Servo.Elevator, Servo.Flap, Servo.Throttle );
			
		}
		
		//Done For Testing Purpose//
		/*---- Controls ----*/
		else if (Cockpit.Auto_Manual_Mode == 1)
		{
			Control.Control_Active = 1000; //This variable indicates that Autopilot is active. (For Logging Purpose)
			call_flight_control();
		}
		/*-----------------*/

		// Transmit Socket Data
		OFDM.JSB_Sim_Transmit_Data();
//		FCC_Veronte.Transmit_Data();
		

		// Transmit Serial Data


		// Log HILS_HUB Data
		Log_Data();
	}
}



void Initialize_Variable()

{
	int index = 0;
	// Reference address to transmit 
	JSBSIM.Out_Data[index++] = &JSBSIM.de_Cmd_Norm;
	JSBSIM.Out_Data[index++] = &JSBSIM.da_Cmd_Norm;
	JSBSIM.Out_Data[index++] = &JSBSIM.dt_Cmd_Norm;
	JSBSIM.Out_Data[index++] = &JSBSIM.df_Cmd_Norm;

	index = 0;
	JSBSIM.Out_Cmd[index++] =	"set fcs/elevator-cmd-norm ";
	JSBSIM.Out_Cmd[index++] =	"set fcs/aileron-cmd-norm ";
	JSBSIM.Out_Cmd[index++] =	"set fcs/throttle-cmd-norm ";
	JSBSIM.Out_Cmd[index++] =	"set fcs/flap-cmd-norm ";


	Cockpit.Keyboard.Aileron = 0;
	Cockpit.Keyboard.Elevator = 0;
	Cockpit.Keyboard.Flap = 0;
	Cockpit.Keyboard.Rudder = 0;
	
	Cockpit.Keyboard.Throttle = 1;
	Cockpit.Keyboard.Trim.Aileron = 0.0;
	Cockpit.Keyboard.Trim.Elevator = -15.0; //This change is done for inintial problem with elevator norm command send to JSBSIM.
	Cockpit.Keyboard.Trim.Flap = 0;
	
	Cockpit.Keyboard.Trim.Rudder = 0;
	Cockpit.Keyboard.Trim.Throttle = 1.0;
	Cockpit.Auto_Manual_Mode = 0;
	Cockpit.Terminate = 0;
	
	Cockpit.Throttle = 1.0;
	JSBSIM.Rx_Status.Flags.Rx_Sync = 0;	
	
	
	Servo.Aileron	= 0.0;
	Servo.Elevator	= 0.0;
	Servo.Flap		= 0.0;
	Servo.Rudder	= 0.0;
	Servo.Throttle	= 1.0;


	Simulation.Time= 0;
	Simulation.JSB_Sim_Data_Rec_Counter = 0;
	Simulation.Veronte_Data_Rec_Counter = 0;


}




void Initilalize_HILS_HUB_Log()
{
	string Str =	"Hub_Sim_Time,"\
					"JSB_Simulation_Time,"\
					"Veronte_Data_Rec_Counter,"\
					"JSB_Sim_Data_Rec_Counter,"\

					"IMU_Lat,"\
					"IMU_Long,"\
					"IMU_Alt,"\
					"IMU_AGL,"\

					"Phi_Rad,"\
					"Theta_Rad,"\
					"Psi_Rad,"\
					"Roll_Rate_Rps,"\

					"Pitch_Rate_Rps,"\
					"Yaw_Rate_Rps,"\
					"System_Elevator_Cmd,"\
					"System_Aileron_Cmd,"\

					"System_Flaps_Cmd,"\
					"System_Throttle_Cmd,"\
					"TAS_MPS,"\
					"Heading_Rad,"\
					"SOG_MPS,"\

					"x_Acc_Mps,"\
					"y_Acc_Mps,"\
					"z_Acc_Mps,"\
					"u_Mps,"\

					"v_Mps,"\
					"w_Mps,"\
					"ROC_Mps,"\
					"JSBSIM_Elevator_Cmd,"\

					"JSBSIM_Aileron_Cmd,"\
					"JSBSIM_Flap_Cmd,"\
					"JSBSIM_Throttle_Cmd,"\
					"Guidance_Velocity_Setpoint,"\
					"Guidance_Altitude_Setpoint,"\
					"Guidance_Heading_Setpoint,"\
					"Gamma_cmd,"\
					"Phi_cmd,"\
					"Theta_cmd,"\
					"p_cmd,"\
					"q_cmd,"\
					"Mode\n";
	
	HILS_HUB_Logg.Open(&(In_System_Log_HILS_HUB.My_File),"LogFile_HILS_HUB.csv");
	HILS_HUB_Logg.Store_String(&(In_System_Log_HILS_HUB.My_File),Str);
}

void Close_HILS_HUB_Log()
{
	HILS_HUB_Logg.Close(&(In_System_Log_HILS_HUB.My_File));
}


void Log_Data()
{
	char Str_char[1024];

	sprintf_s(Str_char, "%d,%f,%d,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%d\n,",\
						\
						Simulation.Time,
						JSBSIM.Simulation_Time,
						Simulation.Veronte_Data_Rec_Counter,
						Simulation.JSB_Sim_Data_Rec_Counter,\
						\
						System_States.IMU_Position.Lat * 57.29,
						System_States.IMU_Position.Long * 57.29,
						System_States.IMU_Position.Alt, //changed the units of Altitude
						JSBSIM.HaGL * 3.32,\
						\
						System_States.Angle.Phi * 57.29,
						System_States.Angle.Theta * 57.29,
						System_States.Angle.Psi * 57.29,
						System_States.Rate.p_RPS * 57.29,\
						\
						System_States.Rate.q_RPS * 57.29,
						System_States.Rate.r_RPS * 57.29,
						Servo.Elevator,
						Servo.Aileron,\
						\
						Servo.Flap,
						Servo.Throttle,
						JSBSIM.TAS_MPS,
						Estimated_Sensors.Heading,\
						JSBSIM.Ground_Speed_MPS,\
						\
						System_States.Acceleration.u_MPS,
						System_States.Acceleration.v_MPS,
						System_States.Acceleration.w_MPS,
						System_States.Velocity.u_MPS,\
						\
						System_States.Velocity.v_MPS,
						System_States.Velocity.w_MPS,
						JSBSIM.Hdot * 3.32,
						JSBSIM.de_Cmd_Norm,\
						\
						JSBSIM.da_Cmd_Norm,
						JSBSIM.df_Cmd_Norm,
						JSBSIM.dt_Cmd_Norm,
						\
						Guidance.Velocity_Setpoint,
						Guidance.Altitude_Setpoint,
						Guidance.Heading_Setpoint,
						Control.Pos_Controller.Gamma_Cmd,
						Control.Pos_Controller.Phi_Cmd,
						Control.Pos_Controller.Theta_Cmd,
						Control.Attitude_Controller.p_Cmd,
						Control.Attitude_Controller.q_Cmd,
						Control.Control_Active
						);
	
	HILS_HUB_Logg.Store_Buffer(&(In_System_Log_HILS_HUB.My_File),Str_char);

}


void JSB_Sim_Send_Cmd_Thread(void * Dummy)
{
	OFDM.JSB_Sim_Transmit_Data();
}

void JSB_Sim_Rec_Ack_Thread(void * Dummy)
{
	OFDM.JSB_Sim_Rec_Ack();
}

void JSB_Sim_Rec_Telemetry_Thread(void * Dummy)
{

	OFDM.JSB_Sim_Receive_Data();
}


void Veronte_Receive_Data_Thread(void * Dummy)
{
	FCC_Veronte.Received_Data();
}


void JSB_Sim_Cockpit_Control_Thread(void * Dummy)
{
	Cockpit_HILS.Joystic();
}
