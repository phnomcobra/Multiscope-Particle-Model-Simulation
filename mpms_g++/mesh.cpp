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
// 11/28/2013 Simplified force diffusion algorithm
// 11/30/2013 Updated remarks
// 12/05/2013 Replaced addseed with addbimap method
// 12/10/2013 Variable time step precision added
///////////////////////////////////////////////////////////////////////

#include "mesh.h"
#include <stdio.h>
#include <time.h>

/* The default constructor for the mesh class uses three integers for defining 
 * the dimensions of the mesh in sectors for the x, y, and z dimensions. A 
 * float is used to specify the size of the cube each sector envelopes. */
mesh::mesh(
	const int &x, 
	const int &y, 
	const int &z, 
	const float &s)
{
	// Initialize mesh dimensions
	sDim = s;
	xSize = x;
	ySize = y;
	zSize = z;
        
	// Set default time step precision
	tPrecision = 1;
        
	// Initialize the number of near and far field sectors
	selts.resize(x * y * z);
	felts.resize(x * y * z);

	// Setup sector indexes
	int sx = 0, sy = 0, sz = 0;
	for(unsigned int i = 0; i < selts.size(); i++)
	{
		// Near field sector's location within the mesh
		selts[i].sx = sx;
		selts[i].sy = sy;
		selts[i].sz = sz;

		// Far field sector's location within the mesh
		felts[i].sx = sx;
		felts[i].sy = sy;
		felts[i].sz = sz;

		// Increment indexes with their respective sizes
		sx++;
		if(sx == xSize)
		{
			sx = 0;
			sy++;
			if(sy == ySize)
			{
				sy = 0;
				sz++;
			}
		}	
	}
}

/* Set time step precision*/
void mesh::settp(const float& tp)
{tPrecision = tp;}

/* Add a particle to the mesh. A reference to a particle object and the sector
 it's being added to is supplied through the arguments.*/
void mesh::addPart(
	const part& newPart, 
	const int& sx, 
	const int& sy, 
	const int& sz)
{selts[getIndex(sx, sy, sz)].pelts.push_back(newPart);}

/* Calculate a sector's index in a vector by its location in the mesh.*/
int mesh::getIndex(const int &x, const int &y, const int &z)
{return x + y * xSize + z * (xSize * ySize);}

/* Add a bilinear matrix to the mesh. For each seed function an affected
 particle type, sampled particle type, number of layers, origins and stepping 
 intervals for temperature and distance must be supplied as arguments.*/
void mesh::addbimat(
	const int& numD, 
	const float& stepD, 
	const float& orgD, 
	const int& numT, 
	const float& stepT, 
	const float& orgT)
{
	bimat newBimat(numD, stepD, orgD, numT, stepT, orgT);
	belts.push_back(newBimat);
}

/* Process the simulation for one frame of time. One or more passes of the 
 near-to-far field sort, sample, time step, and enumeration algorithm is
 executed until t (running sum of time integrated) is equal to 1. The 
 execution time of each algorithm is measured and displayed using clock_t 
 objects. Low energy states of the simulation will require few or even just one
 pass to integrate and maintain integral stability. High energy states require
 large numbers of passes to integrate.*/
void mesh::execute()
{
	// Initialization
	float t = 0, tstep; 
	int numint = 0;
	float timeNear2Far, timeSample, timeGetStep, timeEnum;
	clock_t start, end;
        
	do
	{
		// Near-to-far field sort
		start = clock();
		near2far();
		end = clock();
		timeNear2Far = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
                
		// Localized N-body sampling
		start = clock();
		sample();
		end = clock();
		timeSample = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
                
		// Select and fit time step
		start = clock();
		tstep = getstep();
		if(tstep > 1 - t) tstep = 1 - t;
		t += tstep;
		numint++;
		end = clock();
		timeGetStep = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);

		// Enumeration
		start = clock();
		enumerate(tstep);
		end = clock();
		timeGetStep = 1000 * ((double)(end - start) / CLOCKS_PER_SEC);
                
		// Display execution times
		printf("N2F: %4.0f    SMP: %4.0f    TST: %4.0f    ENM: %4.0f    STP: %3d %4.3f\n", timeNear2Far, timeSample, timeGetStep, timeEnum, numint, t);
	}
	while(t < 1);
}

/* Loop through each sector and get, minimize, and return a time step. The 
 time step returned may not be larger than 1.*/
float mesh::getstep()
{
	float s, tstep = 1;

	for(unsigned int i = 0; i < selts.size(); i++)
	{
		s = selts[i].gettstep(tPrecision);
		if(s < tstep) tstep = s;
	}

	return tstep;
}