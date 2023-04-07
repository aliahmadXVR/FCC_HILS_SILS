#ifndef Includes_Inc
#define Includes_Inc

#include <conio.h>
#include <dos.h>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <process.h>

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <sys/types.h>

#include <time.h>
#include <WS2tcpip.h>
#include <Windows.h>

using namespace std;
#pragma comment (lib, "ws2_32.lib")

/*----
Only Done for Input/Outputs of Controls File
----*/

extern "C"
{
	extern struct	tag_System_States		System_States;
	extern struct	tag_Servo				Servo;
	extern struct	tag_Estimated_Sensors	Estimated_Sensors;
}

#endif
