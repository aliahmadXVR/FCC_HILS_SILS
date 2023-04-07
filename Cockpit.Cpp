#include "stdafx.h"
#define Cockpit_Def
#include "Cockpit.h"





void HILS_Cockpit::Joystic()
{
	
	char Keyboard_In ;
	char Keyboard_In_Old = 0x00;
	unsigned int TimeOut = 0;

	while( Cockpit.Terminate == 0)
	{
		if( _kbhit() ) 
		{
			TimeOut = 0;
			Keyboard_In = _getch();
			if(Keyboard_In_Old == -32) 
			{
				if(Keyboard_In == 'H')	Cockpit.Keyboard.Elevator -= Step_Size;
				if(Keyboard_In == 'P')	Cockpit.Keyboard.Elevator += Step_Size;
			
				if(Keyboard_In == 'K')	Cockpit.Keyboard.Aileron -= Step_Size;
				if(Keyboard_In == 'M')	Cockpit.Keyboard.Aileron += Step_Size;

			}
			else if((Keyboard_In == 'W') || (Keyboard_In == 'w')	)	Cockpit.Keyboard.Flap += Step_Size_Flap;
			else if((Keyboard_In == 'S') || (Keyboard_In == 's')	)	Cockpit.Keyboard.Flap -= Step_Size_Flap;

			else if((Keyboard_In == 'E') || (Keyboard_In == 'e')	)	Cockpit.Keyboard.Throttle += Step_Size_Throttle;
			else if((Keyboard_In == 'D') || (Keyboard_In == 'd')	)	Cockpit.Keyboard.Throttle -= Step_Size_Throttle;

			else if((Keyboard_In == 'T') || (Keyboard_In == 't')	)	Cockpit.Keyboard.Trim.Elevator -= Step_Size_Trim;
			else if((Keyboard_In == 'G') || (Keyboard_In == 'g')	)	Cockpit.Keyboard.Trim.Elevator += Step_Size_Trim;

			else if((Keyboard_In == 'F') || (Keyboard_In == 'f')	)	Cockpit.Keyboard.Trim.Aileron -= Step_Size_Trim;
			else if((Keyboard_In == 'H') || (Keyboard_In == 'h')	)	Cockpit.Keyboard.Trim.Aileron += Step_Size_Trim;
			
			else if((Keyboard_In == 'P') || (Keyboard_In == 'p')	)	Cockpit.Auto_Manual_Mode = 1;
			else if((Keyboard_In == 'O') || (Keyboard_In == 'o')	)	Cockpit.Auto_Manual_Mode = 0;
			else if((Keyboard_In == 'L') || (Keyboard_In == 'l')	)	Cockpit.Terminate = 1;

			if(Cockpit.Keyboard.Elevator > 15.0)				Cockpit.Keyboard.Elevator = 15.0;
			else if(Cockpit.Keyboard.Elevator < -15.0)			Cockpit.Keyboard.Elevator = -15.0;

			if(Cockpit.Keyboard.Trim.Elevator > 15.0)			Cockpit.Keyboard.Trim.Elevator = 15.0;
			else if(Cockpit.Keyboard.Trim.Elevator < -15.0)		Cockpit.Keyboard.Trim.Elevator = -15.0;

			if(Cockpit.Keyboard.Trim.Aileron > 10)				Cockpit.Keyboard.Trim.Aileron = 10;
			else if(Cockpit.Keyboard.Trim.Aileron < -10.0)		Cockpit.Keyboard.Trim.Aileron = -10.0;

			if(Cockpit.Keyboard.Aileron > 10)					Cockpit.Keyboard.Aileron = 10;
			else if(Cockpit.Keyboard.Aileron < -10.0)			Cockpit.Keyboard.Aileron = -10.0;
			
			if(Cockpit.Keyboard.Flap > 10)						Cockpit.Keyboard.Flap = 10;
			else if(Cockpit.Keyboard.Flap < 0.0)				Cockpit.Keyboard.Flap = 0.0;

			if(Cockpit.Keyboard.Throttle > 1.0)					Cockpit.Keyboard.Throttle = 1.0;
			else if(Cockpit.Keyboard.Throttle < 0.0)			Cockpit.Keyboard.Throttle = 0.0;
			
		

			Keyboard_In_Old = Keyboard_In;
		/*	
		printf("cmd , %.3f, %.3f, %.3f, %.3f, %.3f, %.3f\n", Cockpit.Keyboard.Elevator,	Cockpit.Keyboard.Aileron,	Cockpit.Keyboard.Throttle, Cockpit.Keyboard.Flap,
		Cockpit.Keyboard.Trim.Elevator,	Cockpit.Keyboard.Trim.Aileron);
		*/	

//			cout << Keyboard_In << endl; 
		} 

		else
		{
			TimeOut++;
			if(TimeOut > 4096)
			{
				if(Cockpit.Keyboard.Elevator > 0)		Cockpit.Keyboard.Elevator -= Step_Size_AutoCorrect;
				else if(Cockpit.Keyboard.Elevator < 0)		Cockpit.Keyboard.Elevator += Step_Size_AutoCorrect;

					if(Cockpit.Keyboard.Aileron > 0)		Cockpit.Keyboard.Aileron -= Step_Size_AutoCorrect;
				else if(Cockpit.Keyboard.Aileron < 0)		Cockpit.Keyboard.Aileron += Step_Size_AutoCorrect;
			}
		}


		Cockpit.Aileron = Cockpit.Keyboard.Aileron + Cockpit.Keyboard.Trim.Aileron; 
		Cockpit.Elevator = Cockpit.Keyboard.Elevator + Cockpit.Keyboard.Trim.Elevator; 

		Cockpit.Flap = Cockpit.Keyboard.Flap ;
		Cockpit.Throttle = Cockpit.Keyboard.Throttle ;


			


//		printf("cmd , %.2f, %.2f, %.2f, %.2f \n", Cockpit.Aileron,	Cockpit.Elevator,	Cockpit.Flap, Cockpit.Throttle);
	}
	
	
}



