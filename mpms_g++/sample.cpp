///////////////////////////////////////////////////////////////////////
// MESH
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// This class houses the data structure of the simulation. It serves
// as the point of entry for loading particles and seed functions. The
// simulation is executed from this class.
//
// Local N-Body sampling algorithm
//
// ??/??/2013 Original construction
// 11/30/2013 Updated remarks
///////////////////////////////////////////////////////////////////////

#include "mesh.h"

/* Sample thermal and mechanical stress within the mesh. All particles 
 thermal load and acceleration are reset to zero and accumulated from static
 stress and dynamic stress from the sector's far field particles.*/
void mesh::sample()
{
	// Initialization
	part adjPart;
	float4 tCoef;
	sector remoteSector;	
	
	// For each sector
	for(unsigned int i = 0; i < selts.size(); i++)
	{
		// If it has particles
		if(selts[i].pelts.size() > 0)
		{
			// For each particle
			for(unsigned int j = 0; j < selts[i].pelts.size(); j++)
			{
				// Reset acceleration and thermal load
				selts[i].pelts[j].tld = 0;
				selts[i].pelts[j].acc.zero();
				
				// Accumulate static stress
				if(!telts[selts[i].pelts[j].type].isStatic) 
					getStaticStress(selts[i].pelts[j]);
			}

			// Sample dynamic stress from indicated far field
			sector2sector(i);
		}
	}
}

/* Sample dynamic stress from far field sector.*/
void mesh::sector2sector(const int& s)
{
	// Initialization
	float dist;
	
	// For each near field particle
	for(unsigned int i = 0; i < selts[s].pelts.size(); i++)
	{
		// For each far field particle
		for(unsigned int j = 0; j < felts[s].pelts.size(); j++)
		{
			// Distance between sampled and affected particle
			dist = (felts[s].pelts[j].pos - selts[s].pelts[i].pos).mag();

			// If a particle isn't static, accumulate dynamic
			// stress, and isn't referencing itself
			if(dist > 0 && !telts[selts[s].pelts[i].type].isStatic)
				getDynamicStress(selts[s].pelts[i], felts[s].pelts[j]);
		}
	}
}