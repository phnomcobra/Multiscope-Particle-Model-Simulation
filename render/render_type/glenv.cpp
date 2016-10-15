///////////////////////////////////////////////////////////////////////
// RENDER
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// OpenGL Environment 
//
// ??/??/2013 Original Construction
///////////////////////////////////////////////////////////////////////

#include "render.h"

// Set up pixel format for graphics initialization
void SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd, *ppfd;
	int pixelformat;

	ppfd = &pfd;

 	ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	ppfd->nVersion = 1;
	ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	ppfd->dwLayerMask = PFD_MAIN_PLANE;
	ppfd->iPixelType = PFD_TYPE_COLORINDEX;
	ppfd->cColorBits = 16;
	ppfd->cDepthBits = 16;
	ppfd->cAccumBits = 0;
	ppfd->cStencilBits = 0;

	pixelformat = ChoosePixelFormat(hDC, ppfd);
	SetPixelFormat(hDC, pixelformat, ppfd);
}

// Initialize OpenGL graphics
void InitGraphics()
{
	hDC = GetDC(hWnd);

	SetupPixelFormat();

	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	glClearColor(0, 0, 0, 0.5);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
}

// Resize graphics to fit window
void ResizeGraphics()
{
	// Get new window size
	RECT rect;
	int width, height;
	GLfloat aspect;

	GetClientRect(hWnd, &rect);
	width = rect.right;
	height = rect.bottom;
	aspect = (GLfloat)width / height;

	// Adjust graphics to window size
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, aspect, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}
