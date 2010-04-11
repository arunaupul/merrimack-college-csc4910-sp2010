/**
 * @file GlWindow.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Class to handle window create and management
 *
 */

#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include <string>
#include <windows.h>

/**
 * @class GlWindow
 * @brief Window in Windows
 *
 * Class to handle window create and management
 */
class GlWindow {
public:
	/**
	 * Constructor
	 */
	GlWindow();

	/**
	 * Destructor
	 */
	~GlWindow();

	/**
	 * Method to create the window
	 * @param className String to unqiuely ID the class
	 * @param windowTitle Title of the window
	 * @param hInstace Handle to the instance of the object
	 * @param windowPosX X coord to place the window at
	 * @param windowPosY Y coord to place the window at
	 * @param windowWidth Width of the window
	 * @param windowHeight Height of the window
	 * @param fullScreen True if the window should be fullscreen
	 * @param bitsPerPixel Bits per pixel
	 * @param application Pointer to the application running the window
	 * @return True on success
	 */
	bool CreateGlWindow( const std::wstring & className , const std::wstring & windowTitle , HINSTANCE hInstance , int windowPosX , int windowPosY , int windowWidth , int windowHeight , const bool & fullScreen , int bitsPerPixel , LPVOID application );

	/**
	 * Destory and clean up the window
	 */
	void KillWindow();

	/**
	 * Swaps the buffers of the window
	 */
	void SwapBuffers();

	/**
	 * Reshape the gl scene
	 * @param width New window width
	 * @param height New window height
	 */
	void ResizeGlScene( int width , int height );

	/**
	 * Get The Window Height
	 */
	int GetWindowHeight();

	/**
	 * Get The Window Width
	 */
	int GetWindowWidth();

	/**
	 * Overload to allow the GlWindow to act as a HWND
	 * @return The window's Handle
	 */
	operator HWND() { return m_hWnd; }

	/**
	 * Overload to allow the GlWindow to act as a HDC
	 * @return The window's DC
	 */
	operator HDC() { return m_hDc; }

protected:

	/**
	 * Set the window to run in full screen mode
	 * @param windowWidth Width of the window
	 * @param windowHeight Height of the window
	 * @param bitsPerPixel Bits per pixel
	 */
	void EnableFullScreen( const int & windowWidth , const int & windowHeight , const int & bitsPerPixel );

private:
	/**
	 * Window Handle
	 */
	HWND m_hWnd;

	/**
	 * Rendering Context
	 */
	HGLRC m_hRc;

	/**
	 * Device Context
	 */
	HDC m_hDc;

	/**
	 * Is the window in full screen mode
	 */
	bool m_isFullScreen;

	/**
	 * Window Height
	 */
	int m_windowWidth;

	/**
	 * Window Width
	 */
	int m_windowHeight;
};

#endif /* _GL_WINDOW_H_ */