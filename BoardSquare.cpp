#include "BoardSquare.h"

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Point.h"
#include "RgbaColor.h"

BoardSquare::BoardSquare( Point point , bool isRed , int row , int column )
:	m_point( point ),
	m_row( row ),
	m_column( column ),
	m_gamePiece( NULL ),
	m_validMove( isRed )
{
	m_color.green = 0;
	m_color.blue = 0;
	m_color.red = ( isRed ? 1.0 : 0 );
}

BoardSquare::~BoardSquare()
{
}

void BoardSquare::Draw()
{
	glColor4d( m_color.red , m_color.green , m_color.blue , m_color.alpha );
	glBegin( GL_QUADS );
		glVertex3d( m_point.x + 1 , m_point.y + 1 , m_point.z );
		glVertex3d( m_point.x + 1 , m_point.y - 1 , m_point.z );
		glVertex3d( m_point.x - 1 , m_point.y - 1 , m_point.z );
		glVertex3d( m_point.x - 1 , m_point.y + 1 , m_point.z );
	glEnd();
	if( m_gamePiece )
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

bool BoardSquare::IsValidMove()
{
	return m_validMove;
}

int BoardSquare::GetRow()
{
	return m_row;
}

int BoardSquare::GetColumn()
{
	return m_column;
}