#include "BoardSquare.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Point.h"
#include "RgbaColor.h"

BoardSquare::BoardSquare( Point point , int row , int column )
:	m_point( point ),
	m_row( row ),
	m_column( column ),
	m_gamePiece( NULL ),
	m_currentStatus( false ),
	m_nextStatus( false )
{
}

BoardSquare::~BoardSquare()
{
}

void BoardSquare::Draw()
{
	glColor4ub( 255 , 255 , 255 , 255 );
	glBegin( GL_LINE_STRIP );
		glNormal3f( 0 , 0 , 1 );
		glVertex3d( m_point.x - 1.0 , m_point.y + 1.0 , m_point.z - 1.0 );	// Top Left Back
		glVertex3d( m_point.x - 1.0 , m_point.y - 1.0 , m_point.z - 1.0 );	// Bottom Left Back
		glVertex3d( m_point.x + 1.0 , m_point.y - 1.0 , m_point.z - 1.0 );	// Bottom Right Back
		glVertex3d( m_point.x + 1.0 , m_point.y + 1.0 , m_point.z - 1.0 );	// Top Right Back
		glNormal3f( -1 , 0 , 0 );
		glVertex3d( m_point.x - 1.0 , m_point.y + 1.0 , m_point.z - 1.0 );	// Top Left Back
		glVertex3d( m_point.x - 1.0 , m_point.y + 1.0 , m_point.z + 1.0 );	// Top Left Front
		glVertex3d( m_point.x - 1.0 , m_point.y - 1.0 , m_point.z + 1.0 );	// Bottom Left Front
		glVertex3d( m_point.x - 1.0 , m_point.y - 1.0 , m_point.z - 1.0 );	// Bottom Right back
	glEnd();
	glBegin( GL_LINE_STRIP );
		glNormal3f( 0 , 0 , 1 );
		glVertex3d( m_point.x + 1.0 , m_point.y + 1.0 , m_point.z + 1.0 );
		glVertex3d( m_point.x + 1.0 , m_point.y - 1.0 , m_point.z + 1.0 );
		glVertex3d( m_point.x - 1.0 , m_point.y - 1.0 , m_point.z + 1.0 );
		glVertex3d( m_point.x - 1.0 , m_point.y + 1.0 , m_point.z + 1.0 );
		glVertex3d( m_point.x + 1.0 , m_point.y + 1.0 , m_point.z + 1.0 );
		glNormal3f( 1 , 0 , 0 );
		glVertex3d( m_point.x + 1.0 , m_point.y + 1.0 , m_point.z - 1.0 );
		glVertex3d( m_point.x + 1.0 , m_point.y - 1.0 , m_point.z - 1.0 );
		glVertex3d( m_point.x + 1.0 , m_point.y - 1.0 , m_point.z + 1.0 );
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d( m_point.x - 1.0 , m_point.y - 1.0 , m_point.z - 1.1 );
		glVertex3d( m_point.x + 1.0 , m_point.y - 1.0 , m_point.z - 1.1 );
		glVertex3d( m_point.x + 1.0 , m_point.y + 1.0 , m_point.z - 1.1 );
		glVertex3d( m_point.x - 1.0 , m_point.y + 1.0 , m_point.z - 1.1 );
	glEnd();
	if( m_gamePiece && m_currentStatus )
	{
		m_gamePiece->Draw();
	}
}

void BoardSquare::SetGamePiece( GamePiece * piece )
{
	m_gamePiece = piece;
	if( m_gamePiece )
	{
		m_gamePiece->SetPoint( m_point );
	}
}

GamePiece * BoardSquare::GetGamePiece()
{
	return m_gamePiece;
}

bool BoardSquare::ContainsPoint( Point point )
{
	if( m_point.x + 1 > point.x && m_point.x - 1 < point.x &&
			m_point.y + 1 > point.y && m_point.y - 1 < point.y )
	{
		return true;
	}
	return false;
}

int BoardSquare::GetRow()
{
	return m_row;
}

int BoardSquare::GetColumn()
{
	return m_column;
}


bool BoardSquare::GetCurrentStatus()
{
	return m_currentStatus;
}

void BoardSquare::SetCurrentStatus( bool status )
{
	m_currentStatus = status;
}

void BoardSquare::SetNextStatus( bool status )
{
	m_nextStatus = status;
}

void BoardSquare::SetNextAsCurrent()
{
	m_currentStatus = m_nextStatus;
	m_nextStatus = false;
}

void BoardSquare::Update( int ticks )
{
}