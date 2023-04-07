/**
* @file Controls.h
* @author Ali Ahmad (Sr. Design Engineer)- Aviation Design Institute, PAC Kamra.
* @date(started) 1 Nov 2018

* @brief Functions/Implementations of Autopilot Controllers. 
*/

#ifndef Controls_Inc
#define Controls_Inc

#include "Structure.h"

/* Roll Controller Gains */
#define Kp_psi 1.2
#define Ki_psi 0
#define Kd_psi 0 

#define Kp_phi 1.8 
#define Ki_phi 0.08 
#define Kd_phi 0

#define Kp_p 1.2//0.05 
#define Ki_p 0.01 
#define Kd_p 0.001 

/* Altitude Controller Gains */
#define Kp_h 0.004
#define Ki_h 0.0006
#define Kd_h 0.0002 //0.0002

#define Kp_g 2.5
#define Ki_g 0.25
#define Kd_g 0.025

#define Kp_th 3.0//0.9
#define Ki_th 0.4//0.2
#define Kd_th 0

#define Kp_pitch_rate 5.0//0.7
#define Ki_pitch_rate 0.2 //0.1
#define Kd_pitch_rate 0


/* Velocity Controller Gains */
#define Kp_Vel 0.2
#define Ki_Vel 0.03
#define Kd_Vel 0

/* Time Step Size For Controller.
   Will be defined Globally afterwards. */
#define	dT	(float) 0.0083 //120Hz (According to JSBSim FDM)

#endif



#ifdef Controls_Def

extern struct	tag_Guidance			Guidance;
extern struct	tag_Control				Control;
extern struct	tag_System_States		System_States;
extern struct	tag_Servo				Servo;
extern struct	tag_Estimated_Sensors	Estimated_Sensors;

/*----
External functions/structures declarations.
This fucntion will be called by the Main HUB file.
----*/
void call_flight_control();

/*----
Internal function/Structures declarations
----*/
void Servo_Translation(void);

/* Functions used in Roll Controller */
void Heading_Control();
void Roll_Att_Control();
void Roll_Rate_Control();

/* Functions used in Altitude Controller */
void Altitude_Control();
void Gamma_Control();
void Pitch_Att_Control();
void Pitch_Rate_Control();

/* Fucntions used in Velocity Controller */
void Velocity_Control();


/* Functions used in Guidance */
void Guidance_Call();

#endif