///////////////////////////////////////////////////////////////////////
// RENDER
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// This is the function definition for rotating the camera from a 
// rotation vector and computing the camera's new forward vector
// after a rotation.
//
// ??/??/2013 Original Construction
///////////////////////////////////////////////////////////////////////

#include "render.h"

void computeCameraVectors()
{
	const float DEG2RAD = 3.141593f / 180;
	float sx, sy, sz, cx, cy, cz, theta;

	// rotation angle about X-axis (pitch)
	theta = cameraRot.x * DEG2RAD;
	sx = sinf(theta);
	cx = cosf(theta);

	// rotation angle about Y-axis (yaw)
	theta = cameraRot.y * DEG2RAD;
	sy = sinf(theta);
	cy = cosf(theta);

	// rotation angle about Z-axis (roll)
 	theta = cameraRot.z * DEG2RAD;
 	sz = sinf(theta);
 	cz = cosf(theta);

 	// determine forward vector
 	cameraForward.x = sy * cz + cy * sx * sz;
 	cameraForward.y = sy * sz - cy * sx * cz;
 	cameraForward.z = cy * cx;
}