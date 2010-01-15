#include "GlApplication.h"

#include <string>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "GlCircle.h"

#define CLASS_NAME L"OpenGl"

// Function prototype for the windows callback message function
LRESULT CALLBACK WindowProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

GlApplication::GlApplication()
:	m_isActive( true ),
	m_applicationRunning( true ),
	m_circleSize( 10 ),
	m_lastTickCount( 0 )
{
	m_color.red = 1.0;
	m_color.green = 1.0;
	m_color.blue = 1.0;
	m_color.alpha = 1.0;
	m_keys.Reset();
}

GlApplication::~GlApplication()
{
	for( std::list<GlCircle *>::iterator iter = m_drawList.begin() ; iter != m_drawList.end() ; ++iter )
	{
		delete (*iter);
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
	if( !m_window.CreateGlWindow( CLASS_NAME , L"Test Window" , hInstance , 0 , 60 , 640 , 480 , false , 32 , this ) )
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
			// Call the resize function
			m_window.ResizeGlScene( LOWORD( lParam ) , HIWORD( lParam ) );
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
		case WM_LBUTTONDOWN:
			{
				Point newPoint = GetPointAtCursor( lParam );

				m_drawList.push_back( new GlCircle( m_circleSize , newPoint , m_color ) );
			break;
		}
		case WM_RBUTTONDOWN:
		{
			Point newPoint = GetPointAtCursor( lParam );

			for( std::list<GlCircle *>::iterator iter = m_drawList.begin() ; iter != m_drawList.end() ; ++iter )
			{
				if( (*iter)->ContainsPoint( newPoint )  )
				{
					delete *iter;
					iter = m_drawList.erase( iter );
					// If we removed the last node, we need to stop searching
					if( iter == m_drawList.end() )
						break;

				}
			}
			break;
		}
		case WM_MOUSEWHEEL:
		{
			if( m_keys.GetPressed( 'R' ) )
			{
				m_color.red += (double)GET_WHEEL_DELTA_WPARAM(wParam) * 0.001;
				if( m_color.red < 0.0 )
				{
					m_color.red = 0.0;
				}
				if( m_color.red > 1.0 )
				{
					m_color.red = 1.0;
				}
			}
			if( m_keys.GetPressed( 'B' ) )
			{
				m_color.blue += (double)GET_WHEEL_DELTA_WPARAM(wParam) * 0.001;
				if( m_color.blue < 0.0 )
				{
					m_color.blue = 0.0;
				}
				if( m_color.blue > 1.0 )
				{
					m_color.blue = 1.0;
				}
			}
			if( m_keys.GetPressed( 'G' ) )
			{
				m_color.green += (double)GET_WHEEL_DELTA_WPARAM(wParam) * 0.001;
				if( m_color.green < 0.0 )
				{
					m_color.green = 0.0;
				}
				if( m_color.green > 1.0 )
				{
					m_color.green = 1.0;
				}
			}
			break;
		}
	};
	return DefWindowProc( hWnd , uMsg , wParam , lParam );
}

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

	Point returnPoint = { posX , posY , -1.0 * posZ };
	return returnPoint;
}

void GlApplication::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	glTranslatef(0.0f,0.0f,0.0f);						// Move Left 1.5 Units And Into The Screen 6.0
	for( std::list<GlCircle *>::iterator iter = m_drawList.begin() ; iter != m_drawList.end() ; ++iter )
	{
		(*iter)->Draw();
	}
}

bool GlApplication::Init()
{
	glShadeModel( GL_SMOOTH );							// Enable Smooth Shading
	glClearColor( 0.0f , 0.0f , 0.0f , 0.0f );			// Black Background
	glClearDepth( 1.0f );								// Depth Buffer Setup
	glEnable( GL_DEPTH_TEST );							// Enables Depth Testing
	glDepthFunc( GL_LEQUAL );							// The Type Of Depth Testing To Do
	glHint( GL_PERSPECTIVE_CORRECTION_HINT , GL_NICEST );	// Really Nice Perspective Calculations
	glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );	// Really Nice Perspective Calculations

	return true;										// Return true (Initialization Successful)
}

void GlApplication::Update()
{
	int currentTick = GetTickCount();
	for( std::list<GlCircle *>::iterator iter = m_drawList.begin() ; iter != m_drawList.end() ; ++iter )
	{
		(*iter)->Update( currentTick - m_lastTickCount );
	}
	m_lastTickCount = currentTick;
}