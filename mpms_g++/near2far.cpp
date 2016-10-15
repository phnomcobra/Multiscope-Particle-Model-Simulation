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
// Near-to-far field sorting and spatial shifting algorithm.
//
// ??/??/2013 Original construction
// 11/30/2013 Updated remarks
///////////////////////////////////////////////////////////////////////

#include "mesh.h"

/* Populate the far field sectors with the near field sectors they envelope in
 the mesh. Each particle's position and sector must be converted to the far
 field sector's number system.*/
void mesh::near2far()
{
	// Initialization
	float4 offset;
	int nsx, nsy, nsz, index, sx, sy, sz;
	part p;
	unsigned int j;
        
	// For each corresponding far and near field sector
	for(unsigned int i = 0; i < selts.size(); i++)
	{	
		// If the far field is not empty, clear it!
		if(!felts[i].pelts.empty()) felts[i].pelts.clear();

		// For all 26 sector displacements
		for(sx = -1; sx <= 1; sx++)
		{
			for(sy = -1; sy <= 1; sy++)
			{
				for(sz = -1; sz <= 1; sz++)
				{
					// Calculate new sector location                                  
					nsx = selts[i].sx + sx;
					nsy = selts[i].sy + sy;
					nsz = selts[i].sz + sz;

					// If new location is within the mesh
					if(!(     
						nsx < 0 ||
						nsx >= xSize ||
						nsy < 0||
						nsy >= ySize ||
						nsz < 0 ||
						nsz >= zSize)) 
					{
						// Resolve sector's index
						index = this->getIndex(nsx, nsy, nsz);
                                                
						// Calculate offset
						offset.x = (float)sx * sDim;
						offset.y = (float)sy * sDim;
						offset.z = (float)sz * sDim;
                                                
						// For each particle, apply the
						// offset and add it to the far
						// field sector
						for(j = 0; j < selts[index].pelts.size(); j++)
						{
							p = selts[index].pelts[j];
							p.pos = p.pos + offset;
							felts[i].add(p);
						}
					}
				}
			}
		}
	}
}