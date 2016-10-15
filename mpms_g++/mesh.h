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
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 12/05/2013 Implemented bilinear interpolation matrices and 
//            particle type couplings
// 12/10/2013 Variable time step precision added
///////////////////////////////////////////////////////////////////////

#ifndef _MESH

#define _MESH

#include <vector>
#include "sector.h"
#include "ptype.h"
#include "part.h"
#include "bimat.h"
#include "typecoupling.h"
#include <cstdlib>

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
                
		// Set time step precision
		void settp(const float &tp);
                
		// Add particle to mesh
		void addPart(
			const part& newPart, 
			const int& sx, 
			const int& sy, 
			const int& sz);
                
		// Add bilinear matrix
		void addbimat(
			const int& numD, 
			const float& stepD, 
			const float& orgD, 
			const int& numT, 
			const float& stepT, 
			const float& orgT);
		
		// Process a single frame
		void execute();
		
		// Data
		vector <sector> selts;          // Sectors
		vector <sector> felts;          // Far field sectors
		vector <ptype> telts;           // Particles types
		vector <bimat> belts;           // Bilinear interpolation matrices
		vector <typecoupling> celts;    // Type couplings
		
	private:
		// Internal functions
		void enumerate(const float& tstep);
		float getstep();
		void sample();
		int getIndex(const int &x, const int &y, const int &z);

		// Mesh dimensions
		int xSize; int ySize; int zSize;
				
		// Sector size
		float sDim;
                
		// Time step precision
		float tPrecision;
                
		// Sampling functions
		void sector2sector(const int& s);
		void getStaticStress(part& a);
		void getDynamicStress(part& a, part& b);
         	
		// Near field to far field sort
		void near2far();
};

#endif