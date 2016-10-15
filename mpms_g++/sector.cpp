///////////////////////////////////////////////////////////////////////
// SECTOR
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// /************************************************
// * The Sector Class encapsulates the mechanism and
// * data for running the simulation and			
// * generating images of the simulation. The class
// * contains the particle and container data,     
// * file writing pointer, and several member      
// * functions. These functions include scripting  
// * and image, enumerating particles, invoking    
// * dynamics, and generating a time step.		
// ************************************************/
//
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 11/28/2013 Updated time step algorithm
// 11/30/2013 Updated remarks
// 12/10/2013 Variable time step precision added
///////////////////////////////////////////////////////////////////////

#include "sector.h"

// Add New Particle
void sector::add(const part& pelt) 
{pelts.push_back(pelt);}

// Remove Particle by Index
/* When a particle is selected for removal from a vector of particles, it 
 * assigns the contents of the last particle to its index and a pop back is 
 * invoked, shortening the vector */
void sector::remove(const int& pelti)
{
	for(int i = pelti; i < pelts.size() - 1; i++)
	{
		pelts[i] = pelts[i + 1];
	}
	pelts.pop_back();
}

// Enumerate Particles
/* Loop through the particles in this sector in reverse order and integrate them 
 * by the time step provided. If a particle's time-to-live reaches zero, remove
 it from the this sector.*/
void sector::enumerate(const float &tstep)
{
	for(int i = pelts.size() - 1; i >= 0; i--)
	{
		pelts[i].enumerate(tstep);
		if(pelts[i].ttl == 0) remove(i);
	}
}

// Calculate Time Step
/* Return a time step that stabilizes the integration error of this sector to 
 1 or less. Minimize a time step no greater than one from the inverse 
 magnitudes of each particle's velocity, acceleration, and thermal load.*/
float sector::gettstep(const float &tprec)
{
	float tstep = 1;

	if(pelts.size() > 0)
	{
		float t;
		for(unsigned int i = 0; i < pelts.size(); i++)
		{
			t = tprec / pelts[i].vel.mag();
			if(tstep > t) tstep = t;
                    
			t = tprec / pelts[i].acc.mag();
			if(tstep > t) tstep = t;
                    
			t = tprec / abs(pelts[i].tld);
			if(tstep > t) tstep = t;
		}
	}

	// Return Time Step
	return(tstep);
}