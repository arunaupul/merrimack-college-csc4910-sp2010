/*
 *************************
 **   Ryan Fleming      **
 **   GlWindow          **
 **   Jan 27, 2010      **
 **         ,,,         **
 **        (0 0)        **
 **  ---ooO-(_)-Ooo---  **
 *************************
 * Version 1
 *
 * Class to handle window create and management
 */

#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <string>
#include <windows.h>

class GlWindow
{
public:
	GlWindow();										// Constructor
	~GlWindow();									// Destructor

	// Create the window
	bool CreateGlWindow( const std::wstring & className , const std::wstring & windowTitle , HINSTANCE hInstance , int windowPosX , int windowPosY , int windowWidth , int windowHeight , const bool & fullScreen , int bitsPerPixel , LPVOID application );

	void KillWindow();								// Destory and clean up the window
	void SwapBuffers();								// Swaps the buffers of the window
	void ResizeGlScene( int width , int height );	// Reshape the gl scene
	int GetWindowHeight();							// Get The Window Height
	int GetWindowWidth();							// Get The Window Width
	operator HWND() { return m_hWnd; }				// Overload to allow the GlWindow to act as a HWND
	operator HDC() { return m_hDc; }

protected:

	// Set the window to run in full screen mode
	void EnableFullScreen( const int & windowWidth , const int & windowHeight , const int & bitsPerPixel );

private:
	HWND m_hWnd;									// Window Handle
	HGLRC m_hRc;									// Rendering Context
	HDC m_hDc;										// Device Context
	bool m_isFullScreen;							// Is the window in full screen mode
	int m_windowWidth;								// Window Height
	int m_windowHeight;								// Window Width
};

#endif /* _GL_WINDOW_H_ */