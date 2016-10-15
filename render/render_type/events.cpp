///////////////////////////////////////////////////////////////////////
// RENDER
// Justin Dierking
// 4731 Adwell Loop, Grove City, OH 43123
// (937) 371 6026
// justin.l.dierking.mil@mail.mil
// justin.l.dierking.civ@mail.mil
// phnomcobra@gmail.com
//
// This is a function definition is the event handler for render. The 
// events that are handled are resizing the window, closing the
// window, exiting, left and right mouse buttons, and key board events.
// See code for exact mappings.
//
// ??/??/2013 Original Construction
// 12/03/2013 Adjusted frame event handlers for global numFrames
///////////////////////////////////////////////////////////////////////

#include "render.h"

// Handle window events and messages
LONG WINAPI MainWndProc (HWND hWnd, UINT uMsg, WPARAM  wParam, LPARAM  lParam)
{
	// Initialization
	static bool pan;

	switch (uMsg)
	{
		// Resizing the window
		case WM_SIZE:
			ResizeGraphics();
			break;

		// Closing the window
		case WM_CLOSE: 
			DestroyWindow(hWnd);
			break;
 
		// Exiting the window
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	
		// Left mouse button down
		case WM_LBUTTONDOWN:
			// Start panning the camera
			pan = true;
			return 0;

		// Left mouse button up
		case WM_LBUTTONUP:
			// Stop panning the camera
			pan = false;
			return 0;

		// Depressed keys on the keyboard
		case WM_KEYDOWN: 
			switch (wParam) 
			{
				// w key
				case 0x57:
					// Start moving the camera forward
					moveForward = true;
					return 0;

				// s key
				case 0x53:
					// Start moving the camera backward
					moveBackward = true;
					return 0;
		
		// Pressed c key
		case 0x43:
			// Rotate color maps
			colorScheme++;
			if(colorScheme > 1) colorScheme = 0;
			return 0;

		// Pressed a key
		case 0x41:
			// Retreat to previous frame
			currentFrame--;
			if(currentFrame < 0) currentFrame = numFrames - 1;
			return 0;

		// Pressed d key
		case 0x44:
			// Advance to next frame
			currentFrame++;
			if(currentFrame == numFrames) currentFrame = 0;
			return 0;

		// Pressed r key
		case 0x52:
			// Increase temperature multiplier
			if(colorScheme == 1) tmpMult = tmpMult + .1f;
			return 0;

		// Pressed f key
		case 0x46:
			// Decrease temperature multiplier
			if(colorScheme == 1) tmpMult = tmpMult - .1f;
			return 0;
		}
		return 0;

	// Un-pressed Keys on the keyboard
	case WM_KEYUP: 
		switch (wParam) 
        	{
			// w key
			case 0x57:
				// Stop moving the camera forward
				moveForward = false;
				return 0;
			
			// s key
			case 0x53:
				// Stop moving the camera backward
				moveBackward = false;
				return 0;
		}
		return 0;

	// Moving the mouse
	case WM_MOUSEMOVE:
		// Assign old mouse cursor position
		omx = mx;
        	omy = my;

		// Get the current mouse cursor position
		mx = LOWORD(lParam);
        	my = HIWORD(lParam);
        
		// Bit shifting ?
		if(mx & 1 << 15) mx -= (1 << 16);
        	if(my & 1 << 15) my -= (1 << 16);

		// If panning is turned on
		if(pan)
		{
			// Compute rotation as 10% of the rate of cursor motion
			cameraRot.z = cameraRot.z + .1f * (mx - omx);
			cameraRot.y = cameraRot.y - .1f * (my - omy);
			
			// Rotate the camera
			computeCameraVectors();
		}

		return 0;
 
    	// Default event handler
    	default: 
        	return DefWindowProc (hWnd, uMsg, wParam, lParam); 
        	break; 
	} 
 
	return 1; 
}
