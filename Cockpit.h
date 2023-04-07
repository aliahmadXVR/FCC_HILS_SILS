#ifndef Cockpit_Inc
#define	Cockpit_Inc

#include "Includes.h"
#include "Simulation_Structure.h"
#include "AutoPilot/Structure.h"

#define Step_Size	0.8
#define Step_Size_AutoCorrect	0.017
#define Step_Size_Trim	0.15
#define Step_Size_Throttle	0.05
#define Step_Size_Flap	0.25

class HILS_Cockpit 
{
public:
	void Joystic();
};

#endif


#ifdef	Cockpit_Def

struct tag_Cockpit Cockpit;


#endif

