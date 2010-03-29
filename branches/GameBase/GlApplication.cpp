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

#include "GlApplication.h"

#include <string>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "GlFrameworkObject.h"

#define CLASS_NAME L"OpenGl"

// Function prototype for the windows callback message function
LRESULT CALLBACK WindowProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

// Constructor
GlApplication::GlApplication()
:	m_isActive( true ),
	m_applicationRunning( true ),
	m_lastTickCount( GetTickCount() )
{
	m_keys.Reset();												// Release all the keys
}

// Destructor
GlApplication::~GlApplication()
{
}

// Main program loop
int GlApplication::Main( HINSTANCE hInstance , HINSTANCE prevInstance , LPSTR lpCmdLine , int nCmdShow )
{
	WNDCLASS windowClass;										// Windows Class Structure
	hInstance = GetModuleHandle(NULL);
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw on verical and horizontal resize
	windowClass.lpfnWndProc = WindowProc;						// Window message callback function
	windowClass.cbClsExtra = 0;									// No Extra Window Data
	windowClass.cbWndExtra = 0;									// No Extra Window Data
	windowClass.hInstance = hInstance;							// Set the hInstance
	windowClass.hIcon = LoadIcon( NULL , IDI_WINLOGO );			// Set the default icon
	windowClass.hCursor = LoadCursor( NULL , IDC_ARROW );		// Set the cursor to an arrow
	windowClass.hbrBackground = NULL;							// No Backgroun
	windowClass.lpszMenuName = NULL;							// No Menu Name
	windowClass.lpszClassName = CLASS_NAME;						// Set the class name

	if( !RegisterClass( &windowClass ) )						// Attempt to register the class
	{
		MessageBox( NULL , L"Failed to register the window class." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return -1;
	}

	// Create the window
	if( !m_window.CreateGlWindow( CLASS_NAME , L"Test Window" , hInstance , 0 , 60 , 800 , 600 , false , 32 , this ) )
	{
		return -1;
	}

	if( !Init() )												// Attempt to Init the GlWindow
	{
		return -1;
	}

	MSG msg;

	while( m_applicationRunning )								// Start the message pump
	{
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) )	// Check for new messages
		{
			if( msg.message == WM_QUIT )						// Quit message?
			{
				m_applicationRunning = false;					// Stop the main loop and message pump
			}
			else
			{
				TranslateMessage( &msg );						// Translate the message
				DispatchMessage( &msg );						// Send it out
			}
		}
		else													// No new messages, so run the user program
		{
			if( m_isActive )									// Only run the code if we are active
			{
				Update();										// First update the object list
				Draw();											// Now draw the object list
				m_window.SwapBuffers();							// Swap the drawing buffers
			}

			if( m_keys.GetPressed( VK_ESCAPE ) )				// If the escape key if pressed, exit
			{
				m_applicationRunning = false;					// Stop the app
			}
		}
	}

	m_window.KillWindow();										// Clean up the window

	if( !UnregisterClass( CLASS_NAME , hInstance ) )			// Attempt to unregister the class
	{
		MessageBox( NULL , L"Could Not Unregister Class." , L"Shutdown Error" , MB_OK | MB_ICONINFORMATION );
		hInstance = NULL;
	}

	return 0;
}

// Message Handler
LRESULT GlApplication::MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_ACTIVATE:										// Window Activation message
		{
			if( !HIWORD( wParam ) )								// Check active status
			{
				m_isActive = true;
			}
			else
			{
				m_isActive = false;
			}
			return 0;
		}
		case WM_SYSCOMMAND:										// Grab system commands
		{
			switch( wParam )
			{
				case SC_SCREENSAVE:								// Screen saver attempting to start
				case SC_MONITORPOWER:							// Monitor attempting to enter power save mode
					return 0;									// prevent these form happening
			}
			break;
		}
		case WM_CLOSE:											// Close message
		{
			PostQuitMessage( 0 );								// Send out the quit message
			return 0;
		}
		case WM_SIZE:											// Window resize message
		{
			// Call the resize function
			m_window.ResizeGlScene( LOWORD( lParam ) , HIWORD( lParam ) );
			return 0;
		}
		case WM_KEYDOWN:										// Press key
		{
			m_keys.SetPressed( wParam );						// Update the key handler
			KeyPressed( wParam );
			return 0;
		}
		case WM_KEYUP:											// Release key
		{
			m_keys.SetReleased( wParam );						// Update the key handler
			KeyReleased( wParam );
			return 0;
		}
		case WM_LBUTTONDOWN:									// Left mouse click
		{
			LeftMouseClick( GetPointAtCursor( lParam ) );
			break;
		}
		case WM_RBUTTONDOWN:									// Right mouse click
		{
			RightMouseClick( GetPointAtCursor( lParam ) );
			break;
		}
	};
	return DefWindowProc( hWnd , uMsg , wParam , lParam );		// Let windows handle the rest
}

// Utility Method to convert a windows mouse pos into open gl coords
Point GlApplication::GetPointAtCursor( LPARAM lParam )
{
	int viewport[4];
	double modelView[16];
	double projection[16];
	float winX, winY, winZ;
	double posX, posY, posZ;

	glGetDoublev( GL_MODELVIEW_MATRIX , modelView );
	glGetDoublev( GL_PROJECTION_MATRIX , projection );
	glGetIntegerv( GL_VIEWPORT , viewport );

	winX = LOWORD( lParam );
	winY = (float)viewport[3] - (float)HIWORD( lParam );
	glReadPixels( LOWORD( lParam ) , (int)winY , 1 , 1 , GL_DEPTH_COMPONENT , GL_FLOAT , &winZ );

	gluUnProject( winX , winY , winZ , modelView , projection , viewport , &posX , &posY , &posZ );

	return Point( posX , posY , -1.0 * posZ );
}

// Set up the gl window
bool GlApplication::Init()
{
	glShadeModel( GL_SMOOTH );									// Enable Smooth Shading
	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );					// Gray Background
	glClearDepth( 1.0f );										// Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );									// Enables Depth Testing
	glDepthFunc( GL_LEQUAL );									// The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );		// Really Nice Perspective Calculations
	glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );					// Really Nice Perspective Calculations

	if( !PerformInit() )										// Perform custom app init
	{
		return false;
	}

	return true;												// Return true (Initialization Successful)
}

// User overridable method for init
bool GlApplication::PerformInit()
{
	return true;												// Default to success
}

// Update all objects
void GlApplication::Update()
{
	int currentTick = GetTickCount();
	PerformUpdate( currentTick );								// Perform the actual update
	m_lastTickCount = currentTick;								// Update last tick update time
}

// Draw the scene
void GlApplication::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );		// Clear Screen And Depth Buffer
	glLoadIdentity();											// Reset The Current Modelview Matrix
	//glTranslated( -60.0 , -42.0 , -100.0 );
	glTranslated( -120.0 , -84.0 , -200 );

	// Iterate through the objectList and call draw on each one
	for( std::list< GlFrameworkObject * >::iterator iter = m_objectList.begin() ; iter != m_objectList.end() ; ++iter )
	{
		( *iter )->Draw();
	}
}

// User overridable method for object updates
void GlApplication::PerformUpdate( int currentTick )
{
	// Iterate through the objectList and call draw on each one
	for( std::list< GlFrameworkObject * >::iterator iter = m_objectList.begin() ; iter != m_objectList.end() ; ++iter )
	{
		( *iter )->Update( currentTick - m_lastTickCount );
	}
}

// User overridable method to handle left mouse clicks
void GlApplication::LeftMouseClick( Point & clickedPoint )
{
}

// User overridable method to handle right mouse clicks
void GlApplication::RightMouseClick( Point & clickedPoint )
{
}

// User overridable method to handle key press
void GlApplication::KeyPressed( unsigned int key )
{
}

// User overridable method to handle key release
void GlApplication::KeyReleased( unsigned int key )
{
}