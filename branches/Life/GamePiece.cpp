#include "GamePiece.h"
#include <cmath>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Point.h"
#include "RgbaColor.h"


GamePiece::GamePiece( double radius , Point center , RgbaColor color )
:	m_radius( radius ),
	m_center( center ),
	m_color( color )
{
}

GamePiece::~GamePiece()
{
}

void GamePiece::Draw()
{
	glColor4ub( m_color.red , m_color.green , m_color.blue , m_color.alpha );
	glBegin( GL_POLYGON );
		glNormal3f( 0.0 , 0.0 , 1.0 );
		for( double i = 0 ; i < 72 ; i++ )
		{
			double theta = (double)(i*3.14159*2)/72;
			glVertex3d( ( m_radius * sin(theta) ) + m_center.x , ( m_radius * cos(theta) ) + m_center.y , m_center.z + .25 );
		}
	glEnd();
		
	glBegin( GL_POLYGON );
		glNormal3f( 0.0 , 0.0 , -1.0 );
		for( double i = 0 ; i < 72 ; i++ )
		{
			double theta = (double)(i*3.14159*2)/72;
			glVertex3d( ( m_radius * sin(theta) ) + m_center.x , ( m_radius * cos(theta) ) + m_center.y , m_center.z - .25 );
		}
	glEnd();

	glBegin( GL_QUAD_STRIP );
		for( int i = 0 ; i < 72 ; i++ )
		{
			double theta = (double)(i*3.14159*2)/72;
			double newX = ( m_radius * sin(theta) ) + m_center.x;
			double newY = ( m_radius * cos(theta) ) + m_center.y;
			if( i % 2 )
			{
				// TODO
				glNormal3d( newX , newY , 0.0 );
			}
			if( i % 2 )
			{
				glVertex3d( newX , newY , m_center.z + .25 );
				glVertex3d( newX , newY , m_center.z - .25 );
			}
			else
			{
				glVertex3d( newX , newY , m_center.z + .25 );
				glVertex3d( newX , newY , m_center.z - .25 );
			}
		}
		glVertex3d( m_center.x , ( m_radius + m_center.y ) , m_center.z + .25 );
		glVertex3d( m_center.x , ( m_radius + m_center.y ) , m_center.z - .25 );
	glEnd();
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