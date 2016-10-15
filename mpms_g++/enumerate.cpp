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
// This function integrates all sectors within a mesh by a specified
// time step.
//
// ??/??/2013 Original construction
// 11/28/2013 Updated arguments
// 11/30/2013 Updated remarks
///////////////////////////////////////////////////////////////////////

#include "mesh.h"

/* Integrate all particles in the mesh by the time step inputted. If a particle
 Exceeds the bounds of its sector transfer it to its occupied number system and
 sector. Transferring particles from on sector to another requires that an 
 offset be added to its position to convert it from one number system to 
 another.*/
void mesh::enumerate(const float& tstep)
{
	// Initialization
	float wall = sDim / 2; // Distance for origin to boundary wall
	int dsx, dsy, dsz, nsx, nsy, nsz; // Sector displacement and new sector
	part tempPart;
	
	// Loop through each sector and enumerate for a given time step
	for(unsigned int i = 0; i < selts.size(); i++) 
		selts[i].enumerate(tstep);
	
	// Loop through each sector
	for(unsigned int i = 0; i < selts.size(); i++)
	{
		// Loop through each particle
		for(unsigned int j = 0; j < selts[i].pelts.size(); j++)
		{
			// Calculate sector displacement
			// 0, 0, 0 indicates are particle is still within the 
			// sector
			dsx = (int)(selts[i].pelts[j].pos.x / wall);
			dsy = (int)(selts[i].pelts[j].pos.y / wall);
			dsz = (int)(selts[i].pelts[j].pos.z / wall);
			
			// If a particle is outside the sectors wall
			if(dsx != 0 || dsy != 0 || dsz != 0)
			{
				// Make a temp particle
				tempPart = selts[i].pelts[j];
                                
				// Convert the particle's position to the 
				// sector's number system it has intruded into
				tempPart.pos.x -= (float)(dsx) * sDim;
				tempPart.pos.y -= (float)(dsy) * sDim;
				tempPart.pos.z -= (float)(dsz) * sDim;
				
				// Remove the particle from its old sector
				selts[i].remove(j);
				
				// Increment the particle's sector by its
				// sector displacement
				nsx = selts[i].sx + dsx;
				nsy = selts[i].sy + dsy;
				nsz = selts[i].sz + dsz;
				
				// If the modified particle is within the mesh
				// add it back into the mesh
				if(
					nsx >= 0 && nsx < xSize &&
					nsy >= 0 && nsy < ySize &&
					nsz >= 0 && nsz < zSize)
					selts[getIndex(nsx, nsy, nsz)].add(tempPart);
			}
		}
	}
}