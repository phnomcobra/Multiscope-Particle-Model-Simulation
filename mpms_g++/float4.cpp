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
// 11/30/2013 Updated remarks
// 12/08/2013 Removed aunit member
///////////////////////////////////////////////////////////////////////

#include "float4.h"

// Default Constructor
float4::float4() {zero();}

// Zero
void float4::zero()
{
	x = 0;
	y = 0;
	z = 0;
	w = 0;
}

// Magnitude of this vector
float float4::mag() 
{return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + pow(w, 2));}

// Unit Vector of this vector
float4 float4::unit()
{
	// Initialization
	static float magnitude = float4::mag();	
	static float4 answer;          
	
	// Element division
	if(magnitude != 0)
	{
		answer.x = x / magnitude;
		answer.y = y / magnitude;
		answer.z = z / magnitude;
                answer.w = w / magnitude;
	}

	// Return Object
	return answer;
}

// Subtraction operator overload
float4 float4::operator-(const float4& temp)
{
	static float4 answer;
	
	answer.x = x - temp.x;
	answer.y = y - temp.y;
	answer.z = z - temp.z;
	answer.w = w - temp.w;

	return answer;
}

// Addition operator overload
float4 float4::operator+(const float4& temp)
{
	static float4 answer;
	
	answer.x = x + temp.x;
	answer.y = y + temp.y;
	answer.z = z + temp.z;
	answer.w = w + temp.w;

	return answer;
}

// Element to element product operator overload
float4 float4::operator*(const float4& temp)
{
	static float4 answer;
	
	answer.x = x * temp.x;
	answer.y = y * temp.y;
	answer.z = z * temp.z;
	answer.w = w * temp.w;

	return answer;
}

// Scalar product operator overload
float4 float4::operator*(const float& c)
{
	static float4 answer;
	
	answer.x = x * c;
	answer.y = y * c;
	answer.z = z * c;
	answer.w = w * c;

	return answer;
}

// Element to element division operator overload
float4 float4::operator/(const float4& temp)
{
	static float4 answer;
	
	answer.x = x / temp.x;
	answer.y = y / temp.y;
	answer.z = z / temp.z;
	answer.w = w / temp.w;

	return answer;
}

// Scalar division operator overload
float4 float4::operator/(const float& c)
{
	static float4 answer;
	
	answer.x = x / c;
	answer.y = y / c;
	answer.z = z / c;
	answer.w = w / c;

	return answer;
}