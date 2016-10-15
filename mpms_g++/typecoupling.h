///////////////////////////////////////////////////////////////////////
// TYPECOUPLING
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// Particle type coupling class. This object is used to form a
// thermal/mechanical coupling between two particle types. A sampled
// type, affected type, bilinear interpolation matric (bimat), and
// algorithm are specified as integers.
// 
// 12/05/2013 Original construction
///////////////////////////////////////////////////////////////////////

#ifndef _TYPECOUPLING

#define _TYPECOUPLING

class typecoupling
{
	public:
		int sType;
		int aType;
		int aIndex;
		int bIndex;
};

#endif
