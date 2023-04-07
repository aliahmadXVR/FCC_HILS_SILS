#ifndef Joystic_Inc
#define Joystic_Inc


#include"Structure.h"
using namespace std;


#define Step_Size	0.5
#define Step_Size_AutoCorrect	0.007
#define Step_Size_Trim	0.05
#define Step_Size_Throttle	0.05
#define Step_Size_Flap	0.25


class Cockpit_HILS 
{
public:
void Joystic ();

};

#endif


#ifdef Joystic_Def

	void Data_Decode(char * Str);
	string Sstream_String (char * Buffer);
	float Stream_Float(char *src, char c, int index) ;

	struct tag_Cockpit Cockpit;
#endif
