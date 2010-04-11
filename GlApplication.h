/**
 * @file GlApplication.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Base Class for OpenGl Applications
 * Class handles window setup and message handling
 *
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

/**
 * @class GlApplication
 * @brief Base Class for OpenGl Applications
 *
 * Base Class for OpenGl Applications
 * Class handles window setup and message handling
 */
class GlApplication
{
public:
	/**
	 * Constructor
	 */
	GlApplication();

	/**
	 * Destructor
	 */
	~GlApplication();

	/**
	 * Main program loop
	 * @param hInstance Current Instance of the application
	 * @param prevInstance Parent Instance of the application
	 * @param lpCmdLine Array of command line args
	 * @param nCmdShow 1 if the commandline is showing
	 * @return Exit code of the application
	 */
	int Main( HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow );

	/**
	 * Message Handler
	 * @param hWnd Handle to the current window
	 * @param uMsg The message to handle
	 * @param wParam Parameter 1
	 * @param lParam Parameter 2
	 * @return 0 if all went well
	 */
	LRESULT MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

	/**
	 * Utility Method to convert a windows mouse pos into open gl coords
	 * @param lParam Parameter of the point clicked
	 * @return The OpenGl point clicked
	 */
	Point GetPointAtCursor( LPARAM lParam );

protected:
	/**
	 * Draw the scene
	 */
	virtual void Draw();

	/**
	 * Set up the gl window
	 */
	bool Init();

	/**
	 * User overridable method for init
	 */
	virtual bool PerformInit();

	/**
	 * Update all objects
	 */
	void Update();

	/**
	 * User overridable method for object updates
	 * @param currentTick Current Tick count for the time
	 */
	virtual void PerformUpdate( int currentTick );

	/**
	 * User overridable method to handle left mouse clicks
	 * @param clickedPoint Point Clicked
	 */
	virtual void LeftMouseClick( Point & clickedPoint );

	/**
	 * User overridable method to handle right mouse clicks
	 * @param clickedPoint Point Clicked
	 */
	virtual void RightMouseClick( Point & clickedPoint );

	/**
	 * User overridable method to handle key press
	 * @param key The key pressed
	 */
	virtual void KeyPressed( unsigned int key );

	/**
	 * User overridable method to handle key release
	 * @param key The key released
	 */
	virtual void KeyReleased( unsigned int key );

	/**
	 * Key handler for the application
	 */
	KeyHandler m_keys;

	/**
	 * Object list to run update and draw for the application
	 */
	std::list< GlFrameworkObject * > m_objectList;

	/**
	 * Boolean to monitor if the app is running
	 */
	bool m_applicationRunning;

	/**
	 * Last tick count that was run on update
	 */
	int m_lastTickCount;

	/**
	 * The window for the aplication
	 */
	GlWindow m_window;

private:
	/**
	 * Application Instance
	 */
	HINSTANCE hInstance;

	/**
	 * Boolean to monitor if the app is active
	 */
	bool m_isActive;
};

#endif /* _GL_APPLICATION_H_ */