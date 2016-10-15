///////////////////////////////////////////////////////////////////////
// PTYPE
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// Particle type class for static stress characteristics
//
// ??/??/2013 Original construction
// 12/01/2013 Updated remarks
///////////////////////////////////////////////////////////////////////

#ifndef _PTYPE

#define _PTYPE

#include "float4.h"

class ptype
{
	public:
		float	staticDragCoef; // Static drag
		float4	normal;			// Normal acceleration
		bool	isStatic;		// Particle is static
		float4  color;			// Color
		float	tmpLoss;		// Thermal loss
};

#endif