///////////////////////////////////////////////////////////////////////
// PTYPE
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// Particle type class. Objects indicate particle type attributes:
// static drag, normal acceleration, static status, color and
// thermal loss.
//
// ??/??/2013 Original construction
// 11/30/2013 Updated remarks
///////////////////////////////////////////////////////////////////////

#ifndef _PTYPE

#define _PTYPE

#include "float4.h"

class ptype
{
	public:
		float	staticDragCoef;
		float4	normal;
		bool	isStatic;
		float4  color;
		float	tmpLoss;
};

#endif