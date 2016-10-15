///////////////////////////////////////////////////////////////////////
// MPMS Entry Point
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// ??/??/2013 Original construction
// 12/05/2013 Implemented particle type couplings and bilinear
//            interpolation matrices
//            Added switches and help message
// 12/10/2013 Variable time step precision switch added
///////////////////////////////////////////////////////////////////////

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "mesh.h"

using namespace std;

FILE* wtstrm;
FILE* rdstrm;

void help()
{
	cout << endl;
	cout << "Usage: mpms_gcc [OPTION]..." << endl;
	cout << "  --help       Displays this help and exit." << endl;
	cout << endl;
	cout << "Optional arguments for frame indexing and time step precision." << endl;
	cout << "  -b frame     Set the beginning frame number; overrides " << endl;
	cout << "               default frame number of 0." << endl;
	cout << "  -e frame     Set the ending frame number; overrides number of" << endl;
	cout << "               frames in defined in mesh." << endl;
	cout << "  -t precision Set the time step precision." << endl;
	cout << endl;
	cout << "Exit status:" << endl;
	cout << "0  if OK," << endl;
	cout << "1  if minor problems" << endl;
	cout << "2  if serious trouble" << endl;
	cout << endl;
}

int main(int argc, char** argv) 
{
	// Load Mesh ///////////////////////////////////////////////////////////
	rdstrm = fopen("mesh.dat", "r");
	
	// Create and Configure Mesh
	int xSize, ySize, zSize, numFrames, numThreads;
	float sDim;
	fscanf(rdstrm, "%i %i %i %f %i %f", 
		&xSize,         // Number of sectors along x axis
		&ySize,         // Number of sectors along y axis
		&zSize,         // Number of sectors along z axis
		&sDim,          // Width of a sector
		&numFrames,     // Number of frames to simulate
		&numThreads);   // Number of threads (not implemented!)
	mesh a(xSize, ySize, zSize, sDim);
	
	// Load Particle Type Definitions
	int numPtypes;
	fscanf(rdstrm, "%i", &numPtypes);
	a.telts.resize(numPtypes);
	for(int i = 0; i < numPtypes; i++)
	{
		fscanf(rdstrm, "%f %f %f %f %i %f %f %f %f",
			&a.telts[i].staticDragCoef,	// Static drag
			&a.telts[i].normal.x,      	// Normal acceleration
			&a.telts[i].normal.y, 
			&a.telts[i].normal.z,
			&a.telts[i].isStatic,    	// Static indicator
			&a.telts[i].color.x,		// Color
			&a.telts[i].color.y, 
			&a.telts[i].color.z,
			&a.telts[i].tmpLoss); 		// Thermal loss
	}

	// Particle Type Couplings
	int numCouplings;
	fscanf(rdstrm, "%i", &numCouplings);
	a.celts.resize(numCouplings);
	for(int i = 0; i < numCouplings; i++)
	{
		fscanf(rdstrm, "%i %i %i %i",
			&a.celts[i].aType,      // Affected particle type
			&a.celts[i].sType,      // Sampled particle type
			&a.celts[i].bIndex,     // Bimat index
			&a.celts[i].aIndex);    // Algorithm index
	}
       
	// Bilinear Interpolation Matrices
	int numBimats, numD, numT;
	float dOrg, dStep, tOrg, tStep, v;
	fscanf(rdstrm, "%i", &numBimats);
	for(int i = 0; i < numBimats; i++)
	{
		// Read header
		fscanf(rdstrm, "%i %f %f %i %f %f",
			&numD, 		// Number of distance data points
			&dOrg,  	// Origin of distance interval
			&dStep, 	// Distance step size
			&numT, 		// Number of temperature data points
			&tOrg, 		// Origin of temperature interval
			&tStep);	// Temperature step size
		
		// Add a new bilinear interpolation matrix to the mesh
		a.addbimat(numD, dStep, dOrg, numT, tStep, tOrg);
                
		// Populate the matrix
		for(int d = 0; d < numD; d++)
		{
			for(int t = 0; t < numT; t++)
			{
				fscanf(rdstrm, "%f", &v);
				a.belts[i].set(d, t, v);
			}
		}
	}
	fclose(rdstrm);

    
        
	// Switches and Overrides //////////////////////////////////////////////
	int beginFrame = 0, lastFrame = numFrames - 1;
	for(int i = 0; i < argc; i++)
	{
		if((string)argv[i] == "-b")
		{
			if(i + 1 < argc)
				sscanf(argv[i + 1], "%i", &beginFrame);
			else
			{
				cout << "Malformed -b switch!" << endl;
				help();
				return 2;   
			}
		}
                
		if((string)argv[i] == "-e")
		{
			if(i + 1 < argc)
				sscanf(argv[i + 1], "%i", &lastFrame);
			else
			{
				cout << "Malformed -e switch!" << endl;
				help();
				return 2;   
			}
		}
                
		if((string)argv[i] == "-t")
		{
			if(i + 1 < argc)
			{
				float tp;
				sscanf(argv[i + 1], "%f", &tp);
				a.settp(tp);
			}
			else
			{
				cout << "Malformed -t switch!" << endl;
				help();
				return 2;   
			}
		}
                
		if((string)argv[i] == "--help")
		{
			help();
			return 0;   
		}
	}
        
        
        
	// Load Particles //////////////////////////////////////////////////////
	char filename[50];
	sprintf(filename, "playback/part.dat.%i", beginFrame);	
	rdstrm = fopen(filename, "r");
	int sx, sy, sz, numParts;
	part newPart;
	fscanf(rdstrm, "%i", &numParts);
	for(int i = 0; i < numParts; i++)
	{
		fscanf(rdstrm, "%i %i %i %f %f %f %f %f %f %i %f %f",
			&sx,            // Sector
			&sy, 
			&sz,
			&newPart.pos.x, // Position
			&newPart.pos.y, 
			&newPart.pos.z,
			&newPart.vel.x, // Velocity
			&newPart.vel.y, 
			&newPart.vel.z,
			&newPart.type,  // Type
			&newPart.ttl,   // Time to live
			&newPart.tmp);  // Temperature
			
		// Add particle to mesh
		a.addPart(newPart, sx, sy, sz);
	}
	fclose(rdstrm);
        
        
        
	// Process Simulation //////////////////////////////////////////////////
	for(int f = beginFrame + 1; f <= lastFrame; f++)
	{
		a.execute();
                
		sprintf(filename, "playback/part.dat.%i", f);	
		printf("frame %s \n", filename);
               
		wtstrm = fopen(filename, "w");

		// Count and write the number of particles in the mesh
		numParts = 0;
		for(unsigned int i = 0; i < a.selts.size(); i++) 
			numParts += a.selts[i].pelts.size();
		fprintf(wtstrm, "%i\n", numParts);
	
		// Loop through each sector in the mesh and write particle data
		for(unsigned int i = 0; i < a.selts.size(); i++)
		{
			for(unsigned int j = 0; j < a.selts[i].pelts.size(); j++)
			{
				fprintf(wtstrm, "%i %i %i %f %f %f %f %f %f %i %f %f\n",
					a.selts[i].sx,             	// Sector
					a.selts[i].sy, 
					a.selts[i].sz,
					a.selts[i].pelts[j].pos.x, 	// Position
					a.selts[i].pelts[j].pos.y, 
					a.selts[i].pelts[j].pos.z,
					a.selts[i].pelts[j].vel.x, 	// Velocity
					a.selts[i].pelts[j].vel.y, 
					a.selts[i].pelts[j].vel.z,
					a.selts[i].pelts[j].type,  	// Type
					a.selts[i].pelts[j].ttl,   	// Time to live
					a.selts[i].pelts[j].tmp); 	// Temperature
			}
		}
	
		fclose(wtstrm);
	}
    
	return 0;    
}