///////////////////////////////////////////////////////////////////////
// MESH (Render Version)
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
// In render, the mesh class is only needed for managing and accessing
// the data structure of the simulation. All unnecessary members and 
// classes have been remarked for use from within render.
//
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 12/01/2013 Remarked un-needed code for render
///////////////////////////////////////////////////////////////////////

#ifndef _MESH

#define _MESH

#include <vector>
#include "sector.h"
#include "ptype.h"
#include "part.h"
// #include "seed.h"
// #include <cstdlib>

using namespace std;

class mesh
{
	public:
		// Default mesh constructor
		mesh(
			const int &x, 
			const int &y, 
			const int &z, 
			const float &s);
                
		// Add particle to mesh
		void addPart(
			const part& newPart, 
			const int& sx, 
			const int& sy, 
			const int& sz);
                
		/* Add seed function to mesh
		void addSeed(
			const int& aType, 
			const int& sType, 
			const int& numLayers, 
			const int& numD, 
			const float& stepD, 
			const float& orgD, 
			const int& numT, 
			const float& stepT, 
			const float& orgT); */
		
		/* Process a single frame
		void execute(); */
		
		// Data
		vector <sector> selts;		// Near field sectors
		// vector <sector> felts;	// Far field sectors
		vector <ptype> telts;		// Particles types
		// vector <seed> welts;		// Seed functions
		
	private:
		/* Internal functions
		void enumerate(const float& tstep);
		float getstep();
		void sample(); */
		int getIndex(const int &x, const int &y, const int &z);

		// Mesh dimensions
		int xSize; int ySize; int zSize;
				
		// Sector size
		float sDim;
		
		/* Sampling functions
		void sector2sector(const int& s);
		void getStaticStress(part& a);
		void getDynamicStress(
			part& a, 
			part& b, 
			const float& dOrg, 
			const float& tmp); */
		
		/* Near field to far field sort
		void near2far(); */
};

#endif