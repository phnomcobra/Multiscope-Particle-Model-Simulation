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
// Dynamic undergone stress.
//
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 11/28/2013 Simplified force diffusion algorithm
// 12/05/2013 Recoded function for using type couplings and bilinear
//            interpolation matrices.
// 12/08/2013 Brought back original dampening algorithm. Conservation
//            of rotational energy was being broken. Dampening 
//            coefficient is being calculated using enumeration.
///////////////////////////////////////////////////////////////////////

#include "mesh.h"

/* Sample the dynamic stress of each particle. This function lies at the heart
 of the MPMS program. Particle A's affected type and particle B's sampled type
 are matched to one or multiple bilinear interpolation matrices and algorithms. */
void mesh::getDynamicStress(
	part& a, 
	part& b)
{
	// Transfer coefficient
	float4 tcoef = (b.pos - a.pos).unit();
        
	// Distance
	float dist = (b.pos - a.pos).mag();
        
	// Average temperature
	float temp = b.tmp * .5 + a.tmp * .5;
	
	// Dampening coefficient
	part aN = a; aN.enumerate((float)(.001));
	part bN = b; bN.enumerate((float)(.001));
	float coefD = ((aN.pos - bN.pos).mag() - (a.pos - b.pos).mag()) * 1000;
        
	// Loop through each coupling
	for(unsigned int i = 0; i < celts.size(); i++)
	{
		// If affected type and sampled type
		if(celts[i].aType == a.type && celts[i].sType == b.type)
		{	
			switch(celts[i].aIndex)
			{
				case 0:
					// Algorithm 0: Dampening
					a.acc = a.acc + tcoef * (belts[celts[i].bIndex].get(dist, temp) * coefD);
					break;
                                        
				case 1:
					// Algorithm 1: Repulsion/Attraction
					a.acc = a.acc + tcoef * belts[celts[i].bIndex].get(dist, temp);
					break;
                                      
				case 2:
					// Algorithm 2: Thermal Coupling
					a.tld = a.tld + (b.tmp - a.tmp) * belts[celts[i].bIndex].get(dist, temp);
					break;
                                        
				case 3:
					// Algorithm 3: Force Diffusion
					a.acc = a.acc + (b.vel - a.vel) * belts[celts[i].bIndex].get(dist, temp);
					break;
			}
		}
	}
}