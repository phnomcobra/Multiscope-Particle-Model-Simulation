///////////////////////////////////////////////////////////////////////
// RENDER
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// This is a function definition is for loading and initializing a mesh,
// loading particles from each frame, converting the particles to a
// single-scope number system, and building the vector of sectors 
// containing single-scope particles for each frame.
//
// ??/??/2013 Original Construction
///////////////////////////////////////////////////////////////////////
#include "render.h"

void LoadScene()
{
	/* Step one: instantiate a mesh from the mesh.dat file and load
	the particle types into it. Ignore the seed data in the mesh.dat.
	That data will not be needed by render. */
	// Open Mesh
	fopen_s(&rdstrm, "mesh.dat", "r");
	
	// Load mesh configuration
	unsigned int xSize, ySize, zSize, numWorkers;
	float sDim;
	fscanf_s(rdstrm, "%i %i %i %f %i %i", &xSize, &ySize, &zSize, &sDim, &numFrames, &numWorkers);
	
	// Load Particle Type Definitions
	ptype newPtype;
	int numPtypes;
	fscanf_s(rdstrm, "%i", &numPtypes);
	for(int i = 0; i < numPtypes; i++)
	{
		// Static Drag Coef (1 float), Normal (3 floats), Static (1 int), Color (3 floats), Temperature Loss (1 float)
		fscanf_s(rdstrm, "%f %f %f %f %i %f %f %f %f",
			&newPtype.staticDragCoef,
			&newPtype.normal.x, &newPtype.normal.y, &newPtype.normal.z,
			&newPtype.isStatic,
			&newPtype.color.x, &newPtype.color.y, &newPtype.color.z,
			&newPtype.tmpLoss);

		types.push_back(newPtype);
	}

	/* Step two: load the frame's particle file, convert the
	positions to a single-scope number system, and populate a sector.
	Add the product of their sector location and sector dimensions to 
	the particles' positions. Center the positions across the origin. 
	Reduce the positions to 1% of there original value. Repeat step
	for all frames and load into playback vector.*/
	// Initialization
	char filename[50];
	int numParts, sx, sy, sz;
	part newPart;
	float nullF;
	playback.resize(numFrames);
	
	for(unsigned int f = 0; f < numFrames; f++)
	{
		// Determine the file name of the frame
		// This is assumed to be in a subdirectory called playback
		sprintf_s(filename, "playback\\part.dat.%i", f);
	
		// Open the file
		fopen_s(&rdstrm, filename, "r");
		
		// Load Particles
		fscanf_s(rdstrm, "%i", &numParts);
		for(int i = 0; i < numParts; i++)
		{
			// Parse particle
			fscanf_s(rdstrm, "%i %i %i %f %f %f %f %f %f %i %f %f",
			&sx, &sy, &sz,									// sector
			&newPart.pos.x, &newPart.pos.y, &newPart.pos.z,	// position
			&nullF, &nullF, &nullF,							
			&newPart.type,									// type
			&nullF,
			&newPart.tmp);									// temperature
				
			// Compute a reduced and centered single-scope position for each particle
			//     100% Reduction|   Single Scope Conversion    |       Centering
			newPart.pos.x = .01f * (newPart.pos.x + (sx * sDim) - (sDim * xSize) * .5f);
			newPart.pos.y = .01f * (newPart.pos.y + (sy * sDim) - (sDim * ySize) * .5f);
			newPart.pos.z = .01f * (newPart.pos.z + (sz * sDim) - (sDim * zSize) * .5f);
			
			// Add particle to sector
			playback[f].add(newPart);
		}

		// Close file
		fclose(rdstrm);
	}
}