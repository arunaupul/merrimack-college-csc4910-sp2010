#include "GlApplication.h"

#include <string>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <list>

#include "GlObject.h"

#define CLASS_NAME L"OpenGl"

// Function prototype for the windows callback message function
LRESULT CALLBACK WindowProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

GlApplication::GlApplication()
:	m_isActive( true ),
	m_applicationRunning( true ),
	m_lastTickCount( GetTickCount() ),
	m_resizeGlScene( true )
{
	m_keys.Reset();
}

GlApplication::~GlApplication()
{
	for( std::list< GlObject * >::iterator iter = m_objectList.begin() ; iter != m_objectList.end() ; ++iter )
	{
		if( *iter )
		{
			delete *iter;
			*iter = NULL;
		}
	}
}

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
	if( !m_window.CreateGlWindow( CLASS_NAME , L"Test Window" , hInstance , 0 , 60 , 600 , 600 , false , 32 , this ) )
	{
		return -1;
	}

	if( !Init() )
	{
		return -1;
	}

	MSG msg;

	// Start the message pump
	while( m_applicationRunning )
	{
		// Check for new messages
		if( PeekMessage( &msg , NULL , 0 , 0 , PM_REMOVE ) )
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
		else
		{
			if( m_isActive )
			{
				Update();
				Draw();
				m_window.SwapBuffers();
			}

			if( m_keys.GetPressed( VK_ESCAPE ) )
			{
				m_applicationRunning = false;
			}
		}
	}

	m_window.KillWindow();

	if( !UnregisterClass( CLASS_NAME , hInstance ) )			// Attempt to unregister the class
	{
		MessageBox( NULL , L"Could Not Unregister Class." , L"Shutdown Error" , MB_OK | MB_ICONINFORMATION );
		hInstance = NULL;
	}

	return 0;
}

LRESULT GlApplication::MessageHandler( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_ACTIVATE:										// Window Activation message
		{
			if( !HIWORD( wParam ) )								// Check minimized status
			{
				m_isActive = true;
			}
			else
			{
				m_isActive = false;
			}
			return 0;
		}
		case WM_EXITMENULOOP:
		case WM_EXITSIZEMOVE:
		{
			m_lastTickCount = GetTickCount();
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
			if( m_resizeGlScene )
			{
				// Call the resize function
				m_window.ResizeGlScene( LOWORD( lParam ) , HIWORD( lParam ) );
			}
			return 0;
		}
		case WM_KEYDOWN:
		{
			m_keys.SetPressed( wParam );
			return 0;
		}
		case WM_KEYUP:
		{
			m_keys.SetReleased( wParam );
			return 0;
		}
	};
	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}

bool GlApplication::Init()
{
	glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );			// Black Background
	glClearDepth( 1.0f );								// Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
	glDepthFunc( GL_LEQUAL );							// The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );	// Really Nice Perspective Calculations
	glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );			// Really Nice Perspective Calculations

	if( !InitApp() )
	{
		return false;
	}

	return true;										// Return true (Initialization Successful)
}

void GlApplication::Update()
{
	PerformUpdate();
	m_lastTickCount = GetTickCount();
}

void GlApplication::Draw()
{
	for( std::list< GlObject * >::iterator iter = m_objectList.begin() ; iter != m_objectList.end() ; ++iter )
	{
		( *iter )->Draw();
	}											// Finished Drawing The Triangle
}

void GlApplication::PerformUpdate()
{
	int ticksPassed = GetTickCount() - m_lastTickCount;
	for( std::list< GlObject * >::iterator iter = m_objectList.begin() ; iter != m_objectList.end() ; ++iter )
	{
		( *iter )->Update( ticksPassed );
	}
}

void GlApplication::SetResizeGlScene( bool setting )
{
	m_resizeGlScene = setting;
}