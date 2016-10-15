///////////////////////////////////////////////////////////////////////
// FLOAT4
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// /************************************************
// * Float4 data type. Components are                   *
// * composed of floats which default to 0 upon         *
// * initialization. Member functions include		*
// * magnitude and unit vector. The basic math		*
// * operators have been overloaded to interact         *
// * with other float4s. These                          *
// * operations include dot product, scalar		*
// * product, addition, and subtraction.		*
//
// ??/??/2013 Original Construction
// 11/28/2013 Updated operator arguments
// 11/28/2013 Static typing within member functions
// 11/29/2013 Recoded as float4 to make porting to SSE easier
// 12/08/2013 Removed aunit member
///////////////////////////////////////////////////////////////////////


#ifndef _FLOAT4

#define _FLOAT4

#include <cmath>

using namespace std;

class float4
{
	public:	
		// Default Constructor
		float4();		
		
		// Data
		float x, y, z, w;
		
		// Vector Magnitude
		float mag();

		// Unit Vector
		float4 unit();
		
		// Operator Overloading
		float4 operator-(const float4& temp);	
		float4 operator+(const float4& temp); 
		float4 operator*(const float4& temp);
		float4 operator*(const float& c);
		float4 operator/(const float4& temp);	
		float4 operator/(const float& c);

		// Defaults
		void zero();
};

#endif
