#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <string>
#include <windows.h>

class GlWindow
{
public:
	GlWindow();
	~GlWindow();

	// Create the window
	bool CreateGlWindow( const std::wstring & className , const std::wstring & windowTitle , HINSTANCE hInstance , int windowPosX , int windowPosY , int windowWidth , int windowHeight , const bool & fullScreen , int bitsPerPixel , LPVOID application );

	// Destory and clean up the window
	void KillWindow();

	// Swaps the buffers of the window
	void SwapBuffers();

	// Resharp the gl scene
	void ResizeGlScene( int width , int height );

	operator HWND() { return m_hWnd; }

protected:

	// Set the window to run in full screen mode
	void EnableFullScreen( const int & windowWidth , const int & windowHeight , const int & bitsPerPixel );

private:
	HWND m_hWnd;	// Window Handle
	HGLRC m_hRc;	// Rendering Context
	HDC m_hDc;		// Device Context

	bool m_isFullScreen;	// Is the window in full screen mode
};

#endif /* _GL_WINDOW_H_ */