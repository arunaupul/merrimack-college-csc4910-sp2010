#include "GlApplication.h"

#include <string>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "GamePiece.h"
#include "BoardSquare.h"

#define CLASS_NAME L"OpenGl"

// Function prototype for the windows callback message function
LRESULT CALLBACK WindowProc( HWND hWnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

GlApplication::GlApplication()
:	m_isActive( true ),
	m_applicationRunning( true ),
	m_lastTickCount( 0 ),
	m_selectedSpace( NULL ),
	m_playerNumbersTurn( 0 )
{
	m_keys.Reset();

	memset( m_board , 0 , sizeof( BoardSquare * ) * 64 );

	// Build the game board
	bool color = false;
	RgbaColor black = { 0.0 , 0.0 , 0.0 , 0.0 };
	RgbaColor white = { 1.0 , 1.0 , 1.0 , 1.0 };
	for( int row = 0 ; row < NUM_ROWS ; row++ )
	{
		Point currentPoint = { 0 , 0 + ( row * 2 ) , 0 };
		for( int column = 0 ; column < NUM_COLUMNS ; column++ )
		{
			m_board[ ( row * NUM_COLUMNS ) + column ] = new BoardSquare( currentPoint , color , row , column );
			if( row < 3 && color )
			{
				m_board[ ( row * NUM_COLUMNS ) + column ]->SetGamePiece( new GamePiece( .7 , currentPoint , white , true , 0 ) );
			}
			else if( row > 4 && color )
			{
				m_board[ ( row * NUM_COLUMNS ) + column ]->SetGamePiece( new GamePiece( .7 , currentPoint , black , false , 1 ) );
			}
			currentPoint.x += 2;
			color = !color;
		}
		color = !color;
	}

}

GlApplication::~GlApplication()
{
	for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
	{
		delete m_board[pos];
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
			for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
			{
				if( m_board[pos]->ContainsPoint( newPoint ) && m_board[pos]->GetGamePiece() )
				{
					if( m_board[pos]->GetGamePiece()->GetOwnerNumber() == m_playerNumbersTurn )
					{
						m_selectedSpace = m_board[pos];
					}
					break;
				}
			}
			break;
		}
		case WM_RBUTTONDOWN:
		{
			Point newPoint = GetPointAtCursor( lParam );
			if( m_selectedSpace )
			{
				for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
				{
					if( m_board[pos]->ContainsPoint( newPoint ) && m_board[pos]->IsValidMove() )
					{
						AttemptMove( pos );
						break;
					}
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
	glTranslated( -7.0 , -7.0 , -20.0 );				// Move Left 1.5 Units And Into The Screen 6.0

	for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
	{
		if( m_board[pos] != NULL )
		{
			m_board[pos]->Draw();
		}
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
	glHint( GL_LINE_SMOOTH_HINT , GL_NICEST );			// Really Nice Perspective Calculations

	return true;										// Return true (Initialization Successful)
}

void GlApplication::Update()
{
	int currentTick = GetTickCount();
	int ticksPassed = currentTick - m_lastTickCount;
	m_lastTickCount = currentTick;
}

void GlApplication::AttemptMove( int pos )
{
	BoardSquare * moveToSquare = m_board[pos];
	int rowDiff = moveToSquare->GetRow() - m_selectedSpace->GetRow();
	int columnDiff = moveToSquare->GetColumn() - m_selectedSpace->GetColumn();
	bool performMove = false;
	if( !moveToSquare->GetGamePiece() && ( rowDiff > 0 ? m_selectedSpace->GetGamePiece()->CanMoveNorth() : m_selectedSpace->GetGamePiece()->CanMoveSouth() ) )
	{
		// Easy case, move from one row to the next
		if( columnDiff == -1 || columnDiff == 1 )
		{
			performMove = true;
		}
		if( columnDiff == -2 || columnDiff == 2 )
		{
			int jumpedRow = m_selectedSpace->GetRow() + ( rowDiff > 0 ? 1 : -1 );
			int jumpedColumn = m_selectedSpace->GetColumn() + ( columnDiff > 0 ? 1 : -1 );
			BoardSquare * jumpedSpace = m_board[ ( jumpedRow * NUM_COLUMNS ) + jumpedColumn ];
			if( jumpedSpace->GetGamePiece() && jumpedSpace->GetGamePiece()->GetOwnerNumber() != m_playerNumbersTurn )
			{
				performMove = true;
				delete jumpedSpace->GetGamePiece();
				jumpedSpace->SetGamePiece( NULL );
			}
		}

	}
	if( performMove )
	{
		moveToSquare->SetGamePiece( m_selectedSpace->GetGamePiece() );
		m_selectedSpace->SetGamePiece( NULL );

		// Check if piece needs to be kinged
		if( moveToSquare->GetRow() == 0 || moveToSquare->GetRow() == NUM_ROWS - 1 )
		{
			moveToSquare->GetGamePiece()->KingPiece();
		}
		m_playerNumbersTurn = ( m_playerNumbersTurn ? 0 : 1 );
		m_selectedSpace = NULL;
	}
}