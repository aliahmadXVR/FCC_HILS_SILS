/**
* @file Structure.h
* @author Ali Ahmad (Sr. Design Engineer) -- Aviation Design Institute, PAC Kamra.
* @date(started) 1 Nov 2018

* @brief Functions/Implementations of Autopilot Controllers.
*/
#ifndef	Structure_Inc
#define	Structure_Inc

// Interface Structure..............


// ------FCS Interface----------
struct tag_FCS
{
    float TMS_Busy_time;
	unsigned int Counter_5msec;
	float Time;
};


/* -----------------------------------------
These Structures includes all the Control
Input/Output parameters.
------------------------------------------*/



/*----
Servo Structure
----*/
struct tag_Servo
{
	float Aileron;
	float Elevator;
	float Rudder;
	float Flap;
	float Throttle;

	float Servo_1;
	float Servo_2;
	float Servo_3;
	float Servo_4;
	float Servo_5;
	float Servo_6;
};



struct tag_Estimated_Sensors
{
	float Gamma; 
	float Alpha;
	float TAS;
	float Ground_Speed_MPS;
	float Heading;
};



/*----
System States/ Inputs to the Controllers
----*/
struct tag_System_States
{
	struct
	{
		float u_MPS;
		float v_MPS;
		float w_MPS;
	}Acceleration;
	
	struct
	{
		float p_RPS;
		float q_RPS;
		float r_RPS;
	}Rate;
	
	struct
	{
		float u_MPS;
		float v_MPS;
		float w_MPS;
	}Velocity;

	struct
	{
		float Phi;
		float Theta;
		float Psi;
	}Angle;

	struct
	{
		float Lat;
		float Long;
		float Alt;
	}IMU_Position;

	struct
	{
		struct
		{
			float Lat;
			float Long;
			float Alt;
		}Position;
		int Satlites_No;
	}GPS;
};


/*----
Guidance Structure 
----*/
struct tag_Guidance
{
	/* Setpoints For Guidance 
	   (To be shifted to Mission 
	   may be afterwards */
	float Altitude_Setpoint;
	float Heading_Setpoint;
	float Velocity_Setpoint;

	float Lat_Error;
	float Long_Error;
	float Alt_Error;
	float Heading_Error;
	float Speed_Error;

};


/*----
Controller Structures
----*/
struct tag_Control
{
	int Control_Active; //Set to 1000 when Controller active, otherwise 0 on manual mode//

	struct tag_Pos_Controller
	{
		float Phi_Cmd;
		float Gamma_Cmd;
		float Theta_Cmd;
	}Pos_Controller;

	struct tag_Attitude_Controller{
		float p_Cmd;
		float q_Cmd;
		
	}Attitude_Controller;

	struct tag_Velocity_Controller
	{
		float Vel_Cmd;
	}Velocity;


	struct tag_Cmd
	{
		float da_Cmd;
		float de_Cmd;
		float dr_Cmd;
		float dt_Cmd;
		float df_Cmd;
	}Cmd;

};

/*------------------------------------------* /



/*------------------------------Dont use below structures --------------------------------*/

union tag_Temp_Union
{
	

	char C_Temp;
	char C_Temp_Arry[8];
	int I_Temp;
	
	unsigned char UC_Temp;
	unsigned char UC_Temp_Arry[8];
	unsigned int UI_Temp;

	float F_Temp;
	double D_Temp;
	
};



#endif