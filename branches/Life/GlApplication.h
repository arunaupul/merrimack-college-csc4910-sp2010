/*
 *************************
 **   Ryan Fleming      **
 **   GlApplication     **
 **   Jan 27, 2010      **
 **         ,,,         **
 **        (0 0)        **
 **  ---ooO-(_)-Ooo---  **
 *************************
 * Version 1
 *
 * Base Class for OpenGl Applications
 * Class handles window setup and message handling
 */

#ifndef _GL_APPLICATION_H_
#define _GL_APPLICATION_H_

#include <string>
#include <windows.h>
#include <list>
#include "GlWindow.h"
#include "KeyHandler.h"
#include "GlFrameworkObject.h"
#include "Point.h"

class GlApplication
{
public:
	// Constructor
	GlApplication();

	// Destructor
	~GlApplication();

	// Main program loop
	int Main( HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow );

	// Message Handler
	LRESULT MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

	// Utility Method to convert a windows mouse pos into open gl coords
	Point GetPointAtCursor( LPARAM lParam );

protected:
	// Draw the scene
	virtual void Draw();

	// Set up the gl window
	bool Init();

	// User overridable method for init
	virtual bool PerformInit();

	// Update all objects
	void Update();

	// User overridable method for object updates
	virtual void PerformUpdate( int currentTick );

	// User overridable method to handle left mouse clicks
	virtual void LeftMouseClick( Point & clickedPoint );

	// User overridable method to handle right mouse clicks
	virtual void RightMouseClick( Point & clickedPoint );

	// User overridable method to handle key press
	virtual void KeyPressed( unsigned int key );

	// User overridable method to handle key release
	virtual void KeyReleased( unsigned int key );

	// Key handler for the application
	KeyHandler m_keys;

	// Object list to run update and draw for the application
	std::list< GlFrameworkObject * > m_objectList;

	bool m_applicationRunning;		// Boolean to monitor if the app is running

private:
	HINSTANCE hInstance;			// Application Instance
	GlWindow m_window;

	bool m_isActive;				// Boolean to monitor if the app is active

	int m_lastTickCount;			// Last tick count that was run on update
};

#endif /* _GL_APPLICATION_H_ */