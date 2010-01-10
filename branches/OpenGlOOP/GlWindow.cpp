#include "GlWindow.h"

#include <windows.h>
#include <string.h>
#include <gl\gl.h>
#include <gl\glu.h>

GlWindow::GlWindow()
:	m_isFullScreen( false )
{
	m_hWnd = NULL;
	m_hDc = NULL;
	m_hRc = NULL;
}

GlWindow::~GlWindow()
{
	KillWindow();
}

// Create the window
bool GlWindow::CreateGlWindow( const std::wstring & className , const std::wstring & windowTitle , HINSTANCE hInstance , int windowPosX , int windowPosY , int windowWidth , int windowHeight , const bool & fullScreen , int bitsPerPixel , LPVOID application  )
{
	unsigned int pixelFormat;

	PIXELFORMATDESCRIPTOR pfd =											// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),									// Size Of This Pixel Format Descriptor
		1,																// Version Number
		PFD_DRAW_TO_WINDOW	|											// Format Must Support Window
		PFD_SUPPORT_OPENGL	|											// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,												// Must Support Double Buffering
		PFD_TYPE_RGBA,													// Request An RGBA Format
		bitsPerPixel,													// Select Our Color Depth
		0, 0, 0, 0, 0, 0,												// Color Bits Ignored
		0,																// No Alpha Buffer
		0,																// Shift Bit Ignored
		0,																// No Accumulation Buffer
		0, 0, 0, 0,														// Accumulation Bits Ignored
		16,																// 16Bit Z-Buffer (Depth Buffer)
		0,																// No Stencil Buffer
		0,																// No Auxiliary Buffer
		PFD_MAIN_PLANE,													// Main Drawing Layer
		0,																// Reserved
		0, 0, 0															// Layer Masks Ignored
	};

	DWORD windowStyle;													// Window style
	DWORD windowExStyle;												// Window Extended Style
	RECT windowRect;													// Rectangle to define the window size

	// Validate the creation inputs
	if( windowHeight <= 0 )
	{
		windowHeight = 1;
	}
	if( windowWidth <= 0 )
	{
		windowWidth = 1;
	}
	if( bitsPerPixel < 1 )
	{
		bitsPerPixel = 16;
	}

	m_isFullScreen = fullScreen;

	if( m_isFullScreen )
	{
		EnableFullScreen( windowHeight , windowWidth , bitsPerPixel );
	}

	if( m_isFullScreen )
	{
		// If we are still in full screen, reset the screen to 0, 0
		windowPosY = 0;
		windowPosX = 0;
		windowExStyle = WS_EX_APPWINDOW;
		windowStyle = WS_POPUP;
		ShowCursor( false );
	}
	else
	{
		windowExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		windowStyle = WS_OVERLAPPEDWINDOW;
	}

	windowRect.top = windowPosY;
	windowRect.left = windowPosX;
	windowRect.bottom = windowPosY + windowHeight;
	windowRect.right = windowPosX + windowWidth;

	// Adjust the window rect to compensate for the window style
	AdjustWindowRectEx( &windowRect , windowStyle , false , windowExStyle );

	if( windowRect.top < 0 )
	{
		windowRect.bottom -= windowRect.top;
		windowRect.top = 0;
	}
	if( windowRect.left < 0 )
	{
		windowRect.right -= windowRect.left;
		windowRect.left = 0;
	}

	// Attempt to create the window
	// Ok lets attempt to create the window
	if( !( m_hWnd = CreateWindowEx( windowExStyle ,						// Extended style for the window
								className.c_str() ,						// Class name
								windowTitle.c_str() ,					// Window title
								WS_CLIPSIBLINGS	|						// Required for OpenGL
								WS_CLIPCHILDREN |						// Required for OpenGL
								windowStyle ,							// Window Style
								windowPosX , windowPosY ,				// Window Pos
								windowRect.right - windowRect.left ,	// Window width
								windowRect.bottom - windowRect.top ,	// Window height
								NULL ,									// No parent window
								NULL ,									// No menu
								hInstance ,								// the window instance
								application ) ) )						// Pass the Application to the WM_CREATE
	{
		// And we failed
		KillWindow();
		MessageBox( NULL , L"Failed to create the window." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	if( !( m_hDc = GetDC( m_hWnd ) ) )									// Attempt to obtain a device context
	{
		KillWindow();
		MessageBox( NULL , L"Failed to obtain a device context." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	if( !( pixelFormat = ChoosePixelFormat( m_hDc , &pfd ) ) )			// Attempt to find a suitable pixel format
	{
		KillWindow();
		MessageBox( NULL , L"Failed to find a pixel format." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	if( !SetPixelFormat( m_hDc , pixelFormat , & pfd ) )				// Attempt to set the pixel format
	{
		KillWindow();
		MessageBox( NULL , L"Failed to set the pixel format." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	if( !( m_hRc = wglCreateContext( m_hDc ) ) )						// Grab a rendering context
	{
		KillWindow();
		MessageBox( NULL , L"Failed to get a rendering context." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	if( !wglMakeCurrent( m_hDc , m_hRc ) )								// Activate the rendering context
	{
		KillWindow();
		MessageBox( NULL , L"Failed to activate the rendering context." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		return false;
	}

	ShowWindow( m_hWnd , SW_SHOW );										// Show the window
	SetForegroundWindow( m_hWnd );
	SetFocus( m_hWnd );													// Set keyboard focus

	ResizeGlScene( windowWidth , windowHeight );

	return true;
}

void GlWindow::KillWindow()
{
	// If the window is fullscreened, we need to switch to windowed and redisplay the cursor
	// If we don't some gfx cards get upset with us
	if( m_isFullScreen )
	{
		ChangeDisplaySettings( NULL , 0 );								// Switch out of full screen
		ShowCursor( true );												// Display the cursor
	}

	if( m_hRc )															// Only attempt this if the RC has been made
	{
		if( !wglMakeCurrent( NULL , NULL ) )							// Attempt to releas the RC and DC
		{
			MessageBox( NULL , L"Release of RC and DC failed" , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		}
		if( !wglDeleteContext( m_hRc ) )								// Attempt to delete the RC
		{
			MessageBox( NULL , L"Failed to delete the RC." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
		}
		m_hRc = NULL;
	}

	if( m_hDc && !ReleaseDC( m_hWnd , m_hDc ) )							// Attempt to release the DC
	{
		MessageBox( NULL , L"Failed to release the DC." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
	}
	m_hDc = NULL;

	if( m_hWnd && !DestroyWindow( m_hWnd ) )							// Attempt to destory the window
	{
		MessageBox( NULL , L"Error destroying window." , L"Error" , MB_OK | MB_ICONEXCLAMATION );
	}
	m_hWnd = NULL;
}

// Set the window to run in full screen mode
void GlWindow::EnableFullScreen( const int & windowHeight , const int & windowWidth , const int & bitsPerPixel )
{
	DEVMODE dmScreenSettings;
	memset( &dmScreenSettings , 0 , sizeof( dmScreenSettings ) );
	dmScreenSettings.dmSize = sizeof( dmScreenSettings );				// Set the Devmod struct size
	dmScreenSettings.dmBitsPerPel = bitsPerPixel;						// Set the bits per pixel
	dmScreenSettings.dmPelsWidth = windowWidth;							// Set the width
	dmScreenSettings.dmPelsHeight = windowHeight;						// Set the height
	dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

	// Attempt to change into fullscreen mode
	if( ChangeDisplaySettings( &dmScreenSettings , CDS_FULLSCREEN ) != DISP_CHANGE_SUCCESSFUL )
	{
		m_isFullScreen = false;											// And we failed, so run as a window
	}
}

void GlWindow::SwapBuffers()
{
	::SwapBuffers( m_hDc );
}

void GlWindow::ResizeGlScene( int width , int height )
{
	if( height == 0 )											// Prevent 0 height windows
	{
		height = 1;
	}

	glViewport( 0 , 0 , width , height );						// Reset the current Viewport

	glMatrixMode( GL_PROJECTION );								// Select the projection matrix
	glLoadIdentity();											// Reset the matrix

	// Calc the aspect ration
	gluPerspective( 45.0 , (float)width / (float)height , 0.1 , 100.0 );

	glMatrixMode( GL_MODELVIEW );								// Select the matrix model view
	glLoadIdentity();											// Reset the modelview matrix
}