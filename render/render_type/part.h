///////////////////////////////////////////////////////////////////////
// PART
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// /************************************************
// * Particle data type for a spheroid element.    *
// * This data type contains several float4s and   *
// * doubles in an effort to characterize the      *
// * particle's mass, radius, color, undergoing    *
// * force, acceleration, velocity, position, and  *
// * normal acceleration.		           * 
// ************************************************/
//
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 11/30/2013 Updated remarks
///////////////////////////////////////////////////////////////////////


#ifndef _PART

#define _PART

#include "float4.h"

using namespace std;

class part
{
	public:
		// Default Construction
		part();
		
		// Particle Data
		float4 pos;	// Position
		float4 vel;	// Velocity
		float4 acc;	// Undergone Force
		int    type;// Particle Type
		float  ttl;	// Time to Live
		float  tmp;	// Temperature
		float  tld;	// Thermal Load
						
		// Defaults
		void zero();
		
		// Enumerate Particle For the Given Time Step
		void enumerate(const float& tstep);
};

#endif
