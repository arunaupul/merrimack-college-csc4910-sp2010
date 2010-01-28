#include "LifeGame.h"
#include <windows.h>
#include <gl\gl.h>

// Constructor
LifeGame::LifeGame()
:	m_runningSim( false ),
	m_ticksPassed( 0 )
{
	memset( m_board , 0 , sizeof( BoardSquare * ) * NUM_BOARD_SQUARES );

	// Build the game board
	RgbaColor color = { 255 , 0 , 0 , 255 };
	Point dummyPoint = { 0 , 0 , 0 };
	for( int row = 0 ; row < NUM_ROWS ; row++ )
	{
		Point currentPoint = { 0 , 0 + ( row * 2 ) , 0 };
		for( int column = 0 ; column < NUM_COLUMNS ; column++ )
		{
			m_board[row][column] = new BoardSquare( currentPoint , row , column );
			m_board[row][column]->SetGamePiece( new GamePiece( .7 , dummyPoint , color) );
			m_objectList.push_back( m_board[row][column] );		// Add the board piece to the drawing list
			currentPoint.x += 2;
		}
	}
}

// Destructor
LifeGame::~LifeGame()
{
	for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
	{
		if( m_board[0][pos] )
		{
			if( m_board[0][pos]->GetGamePiece() )
			{
				delete m_board[0][pos]->GetGamePiece();
			}
			delete m_board[0][pos];
		}
	}
}

// Override the default perform update
void LifeGame::PerformUpdate( int currentTick )
{
	m_ticksPassed += currentTick;
	if( m_ticksPassed > 300 )
	{
		m_ticksPassed = 0;
		if( m_runningSim )
		{
			for( int row = 0 ; row < NUM_ROWS ; row++ )
			{
				for( int column = 0 ; column < NUM_COLUMNS ; column++ )
				{
					int numberOfNeighbors = 0;
					int tempRow = ( row + 1 == NUM_ROWS ? 0 : row + 1 );
					int tempColumn = ( column - 1 == -1 ? NUM_COLUMNS - 1 : column - 1 );

					// Top Left
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Top
					tempRow = ( row + 1 == NUM_ROWS ? 0 : row + 1 );
					tempColumn = column;
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Top Right
					tempRow = ( row + 1 == NUM_ROWS ? 0 : row + 1 );
					tempColumn = ( column + 1 == NUM_COLUMNS ? 0 : column + 1 );
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Right
					tempRow = row;
					tempColumn = ( column + 1 == NUM_COLUMNS ? 0 : column + 1 );
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Bottom Right
					tempRow = ( row - 1 == -1 ? NUM_ROWS - 1 : row - 1 );
					tempColumn = ( column + 1 == NUM_COLUMNS ? 0 : column + 1 );
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Bottom
					tempRow = ( row - 1 == -1 ? NUM_ROWS - 1 : row - 1 );
					tempColumn = column;
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Bottom Left
					tempRow = ( row - 1 == -1 ? NUM_ROWS - 1 : row - 1 );
					tempColumn = ( column - 1 == -1 ? NUM_COLUMNS - 1 : column - 1 );
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}

					// Left
					tempRow = row;
					tempColumn = ( column - 1 == -1 ? NUM_COLUMNS - 1 : column - 1 );
					if( m_board[tempRow][tempColumn]->GetCurrentStatus() )
					{
						numberOfNeighbors++;
					}


					if( numberOfNeighbors < 2 )
					{
						m_board[row][column]->SetNextStatus( false );
					}
					if( numberOfNeighbors > 3 )
					{
						m_board[row][column]->SetNextStatus( false );
					}
					if( ( numberOfNeighbors == 2 && m_board[row][column]->GetCurrentStatus() ) || numberOfNeighbors == 3 )
					{
						m_board[row][column]->SetNextStatus( true );
					}
				}
			}
			for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
			{
				m_board[0][pos]->SetNextAsCurrent();
			}
		}
	}
}

// Perform custom init code
bool LifeGame::PerformInit()
{
	glClearColor( 0.5f , 0.5f , 0.5f , 0.5f );			// Gray Background

	// Config lighting
	GLfloat LightAmbient[]= { 0.0f, 0.0f, 0.0f, 1.0f };				// Ambient Light Values 
	GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };				// Diffuse Light Values
	GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };			// Light Position

	glLightfv( GL_LIGHT1 , GL_AMBIENT , LightAmbient );
	glLightfv( GL_LIGHT1 , GL_DIFFUSE , LightDiffuse );
	glLightfv( GL_LIGHT1 , GL_POSITION , LightPosition );
	glEnable( GL_COLOR_MATERIAL );
	glEnable( GL_LIGHTING );
	glEnable( GL_LIGHT1 );

	return true;
}

// Override the default left mouse click handler
void LifeGame::LeftMouseClick( Point & clickedPoint )
{
	for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
	{
		if( m_board[0][pos]->ContainsPoint( clickedPoint ) )
		{
			m_board[0][pos]->SetCurrentStatus( true );
			break;
		}
	}
}

// Override the default right mouse click handler
void LifeGame::RightMouseClick( Point & clickedPoint )
{
	for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
	{
		if( m_board[0][pos]->ContainsPoint( clickedPoint ) )
		{
			m_board[0][pos]->SetCurrentStatus( false );
		}
	}
}

// Override the default keypress handler
void LifeGame::KeyPressed( unsigned int key )
{
	if( m_keys.GetPressed( VK_SPACE ) )
	{
		m_runningSim = !m_runningSim;
		m_keys.SetReleased( VK_SPACE );
	}
	if( m_keys.GetPressed( 'C' ) )
	{
		m_keys.SetReleased( 'C' );
		for( int pos = 0 ; pos < NUM_BOARD_SQUARES ; pos++ )
		{
			m_board[0][pos]->SetCurrentStatus( false );
		}
	}
}