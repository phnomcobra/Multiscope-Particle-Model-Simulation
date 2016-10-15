///////////////////////////////////////////////////////////////////////
// RENDER
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// This is a header file for the render application for displaying 
// and animating MPMS data sets. 
//
// 12/01/2013 Original Construction
///////////////////////////////////////////////////////////////////////

#include "render.h"

// These are referenced as external variables in the header!
// Window handles
HWND    hWnd;
HDC     hDC;
HGLRC   hRC;

// File pointer
FILE* rdstrm;

// Scene parameters
float4 cameraPos, cameraForward, cameraRot;
bool moveForward = false, moveBackward = false, redraw = false;
int omx = 0, omy = 0, mx = 0, my = 0, currentFrame = 0, colorScheme = 0;
float tmpMult = .01f;
unsigned int numFrames;

// Playback data
vector <sector> playback;

// Vector of types of particles
vector <ptype> types;

// Entry point of render
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Title Bar
	const LPCWSTR appname = TEXT("MPMS Render");

	WNDCLASS wndclass;
	MSG msg;
 
	// Define the window class
	wndclass.style         = 0;
	wndclass.lpfnWndProc   = (WNDPROC)MainWndProc;
	wndclass.cbClsExtra    = 0;
	wndclass.cbWndExtra    = 0;
	wndclass.hInstance     = hInstance;
	wndclass.hIcon         = LoadIcon(hInstance, appname);
	wndclass.hCursor       = LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndclass.lpszMenuName  = appname;
	wndclass.lpszClassName = appname;
 
 	// Register the window class
	if(!RegisterClass(&wndclass)) return FALSE;
 
	// Create the window
	hWnd = CreateWindow(
		appname,
		appname,
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		NULL,
		NULL,
		hInstance,
		NULL);
	if(!hWnd) return FALSE;

	// Initialize OpenGL
	InitGraphics();

	// Display the window
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Load Playback
	LoadScene();
	
	// Angle Camera
	cameraRot.y = 135;
	cameraRot.z = 45;
	computeCameraVectors();

	// Event loop
	while(1)
	{
		// Check for messages from window
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE) == TRUE)
		{
			if(!GetMessage(&msg, NULL, 0, 0)) return TRUE;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		
		// Move camera forward during moveForward
		if(moveForward)		cameraPos = cameraPos + cameraForward * .5f;
		
		// Move camera backwards during moveBackwards
		if(moveBackward)	cameraPos = cameraPos - cameraForward * .5f;
	
		// Draw Scene :)
		DrawGraphics();
	}

	// Cleanup
	wglDeleteContext(hRC);
	ReleaseDC(hWnd, hDC);
}