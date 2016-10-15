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
///////////////////////////////////////////////////////////////////////

#ifndef _SECTOR

#define _SECTOR

#include <vector>
#include <math.h>
#include "float4.h"
#include "part.h"

using namespace std;

class sector
{
	public:
		// Primary Functions
		void enumerate(const float &tstep);	// Enumerate Particles for a Given Time Step
		float gettstep();					// Generate Time Step

		// Data
		vector <part> pelts;
		void remove(const int& pelti);
		void add(const part& pelt);

		// This Sector's location in the mesh
		int sx, sy, sz;
};

#endif