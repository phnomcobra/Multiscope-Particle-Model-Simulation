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
// * normal acceleration.                          * 
// ************************************************/
//
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 11/30/2013 Updated remarks
///////////////////////////////////////////////////////////////////////

#include "part.h"

// Default Construction
part::part()
{
	type = 0;
	tmp = 0;
	tld = 0;
}

// Zero
void part::zero()
{
	pos.zero();
	vel.zero();
	acc.zero();
}

// Enumerate Particle For the Given Time Step
/* This function employs the Euler method for integration. MPMS is based on
 second order systems composed of acceleration, velocity, position, and first
 order systems consisting of thermal load and temperature. In this function, 
 Euler methods are chained together to form second order integrals to integrate
 a position from a velocity which was integrated from an acceleration. For a 
 given time step, velocity, position, and temperature are calculated and the 
 particle's time-to-live is decremented and floored to zero.*/
void part::enumerate(const float& tstep)
{
	// Integrate Velocity from Acceleration for the Time Step
	vel = vel + acc * tstep;
	
	// Integrate Position from Velocity for the Time Step
	pos = pos + vel * tstep;
	
	// Integrate Temperature from Thermal Load for the Time Step
	tmp = tmp + tld * tstep;

	// Decrement Time To Live
	if(ttl > 0)
	{
		ttl = ttl - tstep;
		if(ttl < 0) ttl = 0;
	}
}