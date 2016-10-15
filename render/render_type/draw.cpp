///////////////////////////////////////////////////////////////////////
// RENDER
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// This is a function definition draws a scene for a selected frame.
// Two color maps are available: thermal and type coloring.
//
// ??/??/2013 Original Construction
///////////////////////////////////////////////////////////////////////

#include "render.h"

// Draw frame
void DrawGraphics()
{
	// Initialization
	float r, g, b, tmp;
	
	// Clear OpenGL buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// Set location in front of camera
	glLoadIdentity();
 	gluLookAt(
		cameraPos.x, 
		cameraPos.y,
		cameraPos.z,
		(cameraPos + cameraForward).x,
		(cameraPos + cameraForward).y,
		(cameraPos + cameraForward).z,
		0, 0, 1);
	
	// Start drawing particles as points
	glBegin(GL_POINTS);
	// For each particle in a frame
	for(unsigned int p = 0; p < playback[currentFrame].pelts.size(); p++)
	{
		// Set color to a 20% saturated hue of what was defined for the type
		if(colorScheme == 0) 
		{
			// Assign color from type
			r = types[playback[currentFrame].pelts[p].type].color.x;
			g = types[playback[currentFrame].pelts[p].type].color.y;
			b = types[playback[currentFrame].pelts[p].type].color.z;

			// Apply 20% saturation
			if(r > .8f) r = .8f; else if(r < 0) r = 0;
			if(g > .8f) g = .8f; else if(g < 0) g = 0;
			if(b > .8f) b = .8f; else if(b < 0) b = 0;
			
			// Set Color
			glColor3f(r + .2f, g + .2f, b + .2f);
		}
		
		// Set color to a 20% saturated hue of RGB color wheel
		if(colorScheme == 1)
		{
			// Load temperature and multiply
			tmp = playback[currentFrame].pelts[p].tmp * tmpMult;
			
			// Compute color wheel
			if(tmp < 1.5708)
			{
				b = cos(tmp);
				g = sin(tmp);
				r = 0;
			}
			else if(tmp < 3.14159)
			{	
				r = -1 * cos(tmp);
				g = sin(tmp);
				b = 0;
			}
			else 
			{
				r = 1;
				g = 0;
				b = 0;
			}

			// Apply 20% saturation
			if(r > .8f) r = .8f; else if(r < 0) r = 0;
			if(g > .8f) g = .8f; else if(g < 0) g = 0;
			if(b > .8f) b = .8f; else if(b < 0) b = 0;
			
			// Set Color
			glColor3f(r + .2f, g + .2f, b + .2f);
		}

		// Set the particle's position as a GLfloat
		glVertex3f(
			(GLfloat)playback[currentFrame].pelts[p].pos.x, 
			(GLfloat)playback[currentFrame].pelts[p].pos.y, 
			(GLfloat)playback[currentFrame].pelts[p].pos.z);
	}
	
	glEnd();	
    
	SwapBuffers(hDC);
}