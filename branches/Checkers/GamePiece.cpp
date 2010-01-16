#include "GamePiece.h"
#include <cmath>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Point.h"
#include "RgbaColor.h"


GamePiece::GamePiece( double radius , Point center , RgbaColor color , bool moveNorth , int ownerNumber )
:	m_radius( radius ),
	m_center( center ),
	m_color( color ),
	m_canMoveNorth( moveNorth ),
	m_king( false ),
	m_ownerNumber( ownerNumber )
{
}

GamePiece::~GamePiece()
{
}

void GamePiece::Draw()
{
	glColor4d( m_color.red , m_color.green , m_color.blue , m_color.alpha );
	glBegin( GL_POLYGON );
		for( double i = 0 ; i < 72 ; i++ )
		{
			double theta = (double)(i*3.14159*2)/72;
			glVertex3d( ( m_radius * sin(theta) ) + m_center.x , ( m_radius * cos(theta) + m_center.y ) , m_center.z );
		}
	glEnd();

	if( m_king )
	{
		double squareSize = sqrt( ( m_radius * m_radius ) / 2.0 );
		glColor4d( 1.0 - m_color.red , 1.0 - m_color.green , 1.0 - m_color.blue , m_color.alpha );
		glBegin( GL_LINE_LOOP );
			glVertex3d( m_center.x + squareSize , m_center.y + squareSize , m_center.z );
			glVertex3d( m_center.x + squareSize , m_center.y - squareSize , m_center.z );
			glVertex3d( m_center.x - squareSize , m_center.y - squareSize , m_center.z );
			glVertex3d( m_center.x - squareSize , m_center.y + squareSize , m_center.z );
		glEnd();
	}
}

bool GamePiece::ContainsPoint( Point point )
{
	if( m_center.x + m_radius > point.x && m_center.x - m_radius < point.x &&
			m_center.y + m_radius > point.y && m_center.y - m_radius < point.y )
	{
		return true;
	}
	return false;
}

void GamePiece::SetPoint( Point newPoint )
{
	m_center = newPoint;
}

bool GamePiece::CanMoveNorth()
{
	return m_king || m_canMoveNorth;
}

bool GamePiece::CanMoveSouth()
{
	return m_king || !m_canMoveNorth;
}

int GamePiece::GetOwnerNumber()
{
	return m_ownerNumber;
}

void GamePiece::KingPiece()
{
	m_king = true;
}