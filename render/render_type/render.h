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

#ifndef _RENDER

#define _RENDER

// Includes ///////////////////////////////////////////////////////////
// OpenGL and Windows environment classes
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

// IO classes
#include <string>
#include <iostream>
#include <stdio.h>

// MPMS classes
#include "float4.h"
#include "part.h"
#include "sector.h"
#include "mesh.h"
#include "ptype.h"

// System namespaces
#using <System.dll>
using namespace std;
using namespace System;
using namespace System::Text;

// External Variables /////////////////////////////////////////////////
/* All external variables have been declared in render.cpp */
// Window handles
extern HWND    hWnd;
extern HDC     hDC;
extern HGLRC   hRC;

// File pointer
extern FILE* rdstrm;

// Scene parameters
extern float4 cameraPos, cameraForward, cameraRot;
extern bool moveForward, moveBackward;
extern int omx, omy, mx, my, currentFrame, colorScheme;
extern unsigned int numFrames;
extern float tmpMult;

// Single scope sector
extern sector singleScope;

// Playback
extern vector <sector> playback;

// Vector of types of particles
extern vector <ptype> types;

// Function Declarations ///////////////////////////////////////////////
void DrawGraphics();
void LoadScene();
void computeCameraVectors();
void SetupPixelFormat();
void InitGraphics();
void ResizeGraphics();
LONG WINAPI MainWndProc (HWND hWnd, UINT uMsg, WPARAM  wParam, LPARAM  lParam);

#endif