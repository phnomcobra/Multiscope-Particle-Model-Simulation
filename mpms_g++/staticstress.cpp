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
// Static undergone stress.
//
// ??/??/2013 Original construction
// 11/30/2013 Updated arguments
///////////////////////////////////////////////////////////////////////

#include "mesh.h"

/* Accumulate static stress for a particle. Thermal loss, normal acceleration,
 and static drag are applied based on the particle's type.*/
void mesh::getStaticStress(part &a)
{
	// Static Thermal Loss
	a.tld = a.tld - a.tmp * telts[a.type].tmpLoss;

	// Normal Acceleration
	a.acc = a.acc + telts[a.type].normal;
	
	// Static Drag
	a.acc = a.acc - a.vel * telts[a.type].staticDragCoef;
}
