///////////////////////////////////////////////////////////////////////
// BIMAT
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// Seed function class.
//
// ??/??/2013 Original construction
// 11/28/2013 Static typing within member functions
// 12/05/2013 Renamed class to bimat (bilinear interpolation matrix)
//            Functionality was redesigned to doing 2d interpolation
//            only without the layering or type interaction parameters
//            from the seed class.
///////////////////////////////////////////////////////////////////////

#include "bimat.h"

/* Add a new seed function to the mesh. For each seed function an affected
 particle type, sampled particle type, number of layers, origins and stepping 
 intervals for temperature and distance must be supplied as arguments.*/
bimat::bimat(
	const int& numD, 
	const float& stepD, 
	const float& orgD, 
	const int& numT, 
	const float& stepT, 
	const float& orgT)
{
	// Initialize seed data as a 2d array
	// Number of distance data points
	data = new float*[numD];
	for(int j = 0; j < numD; j++)
		data[j] =  new float[numT];
	
	// Set temperature interval
	this->minT = orgT;
	this->maxT = orgT + stepT * numT;

	// Set distance interval
	this->minD = orgD;
	this->maxD = orgD + stepD * numD;

	// Set step sizes
	this->stepD = stepD;
	this->stepT = stepT;

	// Set number of data points
	this->numD = numD;
	this->numT = numT;
}

/* Set a data point in 2d array.*/
void bimat::set(
	const int& d, 
	const int& t, 
	const float& v)
{data[d][t] = v;}

/* Get an interpolated value from a distance in temperature. This
 function use linear interpolation. If temperature and/or distance are outside
 of the data sets temperature and distance intervals, a zero is returned.*/
float bimat::get(const float& d, const float& t)
{
	// Initialization
	float iv = 0;
        
	// Data points to interpolate between
	int d0 = (int)((d - minD) / stepD), d1 = d0 + 1;
	int t0 = (int)((t - minT) / stepT), t1 = t0 + 1;

	// If distance and temperature are within data set's intervals
	if(d0 >= 0 && t0 >= 0 && d1 < numD && t1 < numT)
	{
		// Temperature and distance interpolation coefficients
		float nd = d - d0 * stepD;
		float nt = t - t0 * stepT;

		// 2d interpolation
		float i0 = data[d1][t0] * nd / stepD + data[d0][t0] * (stepD - nd) / stepD;
		float i1 = data[d1][t1] * nd / stepD + data[d0][t1] * (stepD - nd) / stepD;
		iv = i1 * nt / stepT + i0 * (stepT - nt) / stepT;
	}

	return iv;
}