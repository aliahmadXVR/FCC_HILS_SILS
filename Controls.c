/**
* @file Controls.c
* @author Ali Ahmad (Sr. Design Engineer)- Aviation Design Institute, PAC Kamra. 
* @date(started) 1 Nov 2018
* @brief Functions/Implementations of Autopilot Controllers.This file includes 
* all the functions related to  Flight Contrller. This file calls all the
* control structures.
*/

#define Controls_Def
#include "Controls.h"

/*
This function is called by the main file.
*/
void call_flight_control(void)
{
	/* Guidance Call */
	Guidance_Call();

	/* Roll Controller */
	Heading_Control();
	Roll_Att_Control();
	Roll_Rate_Control();
	Servo_Translation();
	
	/* Pitch Controller */
	Altitude_Control();
	Gamma_Control();
	Pitch_Att_Control();
	Pitch_Rate_Control();
	Servo_Translation();

	/* Velocity Controller */
	Velocity_Control();

}

/* -------------------------------
Guidance Functions Definations
---------------------------------*/

/* This fucntion generates the Guidance
commands (Description to  be updated 
further) */
void Guidance_Call()
{
	/* Setting Up Setpoints */
	Guidance.Altitude_Setpoint = 500;		//In meters
	Guidance.Heading_Setpoint = 1.4;			//In Rad
	Guidance.Velocity_Setpoint = 170;		//TAS  (mps)

	/* Calculating Errors, these errors are used directly by 
	   individual controllers below. */
	Guidance.Alt_Error = Guidance.Altitude_Setpoint - System_States.IMU_Position.Alt;
	Guidance.Heading_Error = Guidance.Heading_Setpoint - Estimated_Sensors.Heading;
	Guidance.Speed_Error = Guidance.Velocity_Setpoint - Estimated_Sensors.TAS;

/*	 //Old Testing Code//
	Control.Pos_Controller.Phi_Cmd = 0;		//Manually passing Phi- setpoint to Roll controller. Comment Heading_Control() for using this.
	Control.Pos_Controller.Theta_Cmd = 0;	//Manually passing Theta- setpoint to Pitch controller. Comment Altitude_Control() & Gamma_Control() for using this.
	Control.Velocity.Vel_Cmd = 170;			//TAS  (mps)
	*/
}



/* -------------------------------
Roll Control Functions Definations
---------------------------------*/

/* This fucntion generates the Roll
angle (Phi) command */
void Heading_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
 
	//P 
	Pout = Kp_psi * Guidance.Heading_Error;

	//I
	integrator += (Guidance.Heading_Error * dT);
	Iout = Ki_psi * integrator;

	//D
	derivative = (Guidance.Heading_Error - preError) / dT;
	Dout = Kd_psi * derivative;
	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Pos_Controller.Phi_Cmd =pid_out;

	//add saturations/constraints here when required.
	if (Control.Pos_Controller.Phi_Cmd > 1.047)
	{
		Control.Pos_Controller.Phi_Cmd = 1.047;
	}
	if (Control.Pos_Controller.Phi_Cmd < -1.047)
	{
		Control.Pos_Controller.Phi_Cmd = -1.047;
	}

	preError = Guidance.Heading_Error;
}

/* This fucntion generates the Roll
Rate (p) command */
void Roll_Att_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
	float phi_error;

	phi_error = Control.Pos_Controller.Phi_Cmd - System_States.Angle.Phi;

	//P 
	Pout = Kp_phi * phi_error;

	//I
	integrator += (phi_error * dT);
	Iout = Ki_phi * integrator;

	//D
	derivative = (phi_error - preError) / dT;
	Dout = Kd_phi * derivative;
	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Attitude_Controller.p_Cmd = pid_out;

	//add saturations/constraints here when required.
	if (Control.Attitude_Controller.p_Cmd > 1.047)
	{
		Control.Attitude_Controller.p_Cmd = 1.047;
	}
	
	if (Control.Attitude_Controller.p_Cmd < -1.047)
	{
		Control.Attitude_Controller.p_Cmd = -1.047;
	}

	preError = phi_error;
}

/* This fucntion generates the Aileron
Command (Norm) */
void Roll_Rate_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
	float p_error;

	p_error = Control.Attitude_Controller.p_Cmd - System_States.Rate.p_RPS;

	//P 
	Pout = Kp_p * p_error;

	//I
	integrator += (p_error * dT);
	Iout = Ki_p * integrator;

	//D
	derivative = (p_error - preError) / dT;
	Dout = Kd_p * derivative;
	float pid_out = Pout + Iout + Dout;
	 
	//Change this command according to saturations when required.
	Control.Cmd.da_Cmd = pid_out;

	//add saturations/constraints here when required.
	if (Control.Cmd.da_Cmd > 10)
	{
		Control.Cmd.da_Cmd = 10;
	}
	if (Control.Cmd.da_Cmd < -10)
	{
		Control.Cmd.da_Cmd = -10;
	}
	preError = p_error;
}



/* -----------------------------------
Altitude Control Functions Definations
-------------------------------------*/

/* This fucntion generate the
gamma command */
void Altitude_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;

	//P 
	Pout = Kp_h * Guidance.Alt_Error;

	//I
	integrator += (Guidance.Alt_Error * dT);
	Iout = Ki_h * integrator;

	//D
	derivative = (Guidance.Alt_Error - preError) / dT;
	Dout = Kd_h * derivative;
	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Pos_Controller.Gamma_Cmd = pid_out;
	
	//add saturations/constraints here when required.
	if (Control.Pos_Controller.Gamma_Cmd > 0.2618)
	{
		Control.Pos_Controller.Gamma_Cmd = 0.2618;
	}
	if (Control.Pos_Controller.Gamma_Cmd < -0.1745)
	{
		Control.Pos_Controller.Gamma_Cmd = -0.1745;
	}

	preError = Guidance.Alt_Error;
}

/* This fucntion generate the
theta command */
void Gamma_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
	float gamma_error = 0;

	gamma_error = Control.Pos_Controller.Gamma_Cmd - Estimated_Sensors.Gamma;

	//P 
	Pout = Kp_g * gamma_error;

	//I
	integrator += (gamma_error * dT);
	Iout = Ki_g * integrator;

	//D
	derivative = (gamma_error - preError) /dT;
	Dout = Kd_g * derivative;

	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Pos_Controller.Theta_Cmd = pid_out;

	//add saturations/constraints here when required.
	if (Control.Pos_Controller.Theta_Cmd > 0.4363)
	{
		Control.Pos_Controller.Theta_Cmd = 0.4363;
	}
	if (Control.Pos_Controller.Theta_Cmd < -0.2618)
	{
		Control.Pos_Controller.Theta_Cmd = -0.2618;
	}

	preError = gamma_error;
}

/* This fucntion generate the
q command */
void Pitch_Att_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
	float theta_error = 0;

	theta_error = Control.Pos_Controller.Theta_Cmd - System_States.Angle.Theta;

	//P 
	Pout = Kp_th * theta_error;

	//I
	integrator += (theta_error * dT);
	Iout = Ki_th * integrator;

	//D
	derivative = (theta_error - preError) / dT;
	Dout = Kd_th * derivative;

	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Attitude_Controller.q_Cmd = pid_out;

	//add saturations/constraints here when required.
	if (Control.Attitude_Controller.q_Cmd > 1.047)
	{
		Control.Attitude_Controller.q_Cmd = 1.047;
	}
	if (Control.Attitude_Controller.q_Cmd < -1.047)
	{
		Control.Attitude_Controller.q_Cmd = -1.047;
	}
	
	preError = theta_error;
}

/* This fucntion generates the Elevator
Command (Norm) */
void Pitch_Rate_Control()
{

	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
	float q_error = 0;

	q_error = Control.Attitude_Controller.q_Cmd - System_States.Rate.q_RPS;

	//P 
	Pout = Kp_pitch_rate * q_error;

	//I
	integrator += (q_error * dT);
	Iout = Ki_pitch_rate * integrator;

	//D
	derivative = (q_error - preError) / dT;
	Dout = Kd_pitch_rate * derivative;

	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Cmd.de_Cmd = -1 * pid_out; //-1 is multiplied to match the convention with JSBSim.

	//add saturations/constraints here when required.
	if (Control.Cmd.de_Cmd > 15)
	{
		Control.Cmd.de_Cmd = 15;
	}
	if (Control.Cmd.de_Cmd < -15)
	{
		Control.Cmd.de_Cmd = -15;
	}

	preError = q_error;
}


/* -----------------------------------
Velocity Controller Function Defination
-------------------------------------*/

/* This function generates the respective 
normalized Throttle command */
void Velocity_Control()
{
	float Pout = 0, Iout = 0, Dout = 0;
	static float integrator = 0;
	float derivative = 0;
	static float preError = 0;
	
	//P 
	Pout = Kp_Vel * Guidance.Speed_Error;

	//I
	integrator += (Guidance.Speed_Error * dT);
	Iout = Ki_Vel * integrator;

	//D
	derivative = (Guidance.Speed_Error - preError) / dT;
	Dout = Kd_Vel * derivative;
	float pid_out = Pout + Iout + Dout;

	//Change this command according to saturations when required.
	Control.Cmd.dt_Cmd = pid_out; 

	//add saturations/constraints here when required.
	if (Control.Cmd.dt_Cmd < 0.2)
	{
		Control.Cmd.dt_Cmd = 0.2;
	}
	
	if (Control.Cmd.dt_Cmd > 1)
	{
		Control.Cmd.dt_Cmd = 1;
	}

	preError = Guidance.Speed_Error;
}


/* -----------------------------------
Servo  Translation Function Defination
-------------------------------------*/

/* This function generates the repective
   servo commands */
void Servo_Translation(void)
{
	Servo.Aileron = Control.Cmd.da_Cmd;
	Servo.Elevator = Control.Cmd.de_Cmd;
	Servo.Flap = Control.Cmd.df_Cmd;
	Servo.Rudder = 0;
	Servo.Throttle = Control.Cmd.dt_Cmd;
}



