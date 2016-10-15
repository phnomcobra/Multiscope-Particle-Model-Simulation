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

#ifndef _BIMAT

#define _BIMAT

class bimat
{
	public:
		// Default Construction
		bimat(
			const int& numD, 
			const float& stepD, 
			const float& orgD, 
			const int& numT, 
			const float& stepT, 
			const float& orgT);
		
		// Set data point
		void set(
			const int& d, 
			const int& t, 
			const float& v);
                
		// Get interpolated value
		float get(const float& d, const float& t);
		
	private:
		float** data;
		float minD, maxD, stepD, minT, maxT, stepT;
		int numT, numD;
};

#endif