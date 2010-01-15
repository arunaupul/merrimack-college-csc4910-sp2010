#include "GlCircle.h"
#include <cmath>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>

#include "Point.h"
#include "RgbaColor.h"


GlCircle::GlCircle( double radius , Point center , RgbaColor color )
:	m_radius( radius ),
	m_center( center ),
	m_color( color ),
	m_startingRadius( radius ),
	m_tickCount( 0 ),
	m_direction( false )
{
}

GlCircle::~GlCircle()
{
}

void GlCircle::Draw()
{
	glColor4d( m_color.red , m_color.green , m_color.blue , m_color.alpha );
	glTranslated(0.0 , 0.0 , -1*m_center.z );						// Move Left 1.5 Units And Into The Screen 6.0
	glBegin( GL_POLYGON );
		for( double i = 0 ; i < 72 ; i++ )
		{
			double theta = (double)(i*3.14159*2)/72;
			glVertex2d( ( m_radius * sin(theta) ) + m_center.x , ( m_radius * cos(theta) + m_center.y ) );
		}
	glEnd();
	glTranslated(0.0 ,0.0 , m_center.z );						// Move Left 1.5 Units And Into The Screen 6.0
}

bool GlCircle::ContainsPoint( Point point )
{
	if( m_center.x + m_radius > point.x && m_center.x - m_radius < point.x &&
			m_center.y + m_radius > point.y && m_center.y - m_radius < point.y )
	{
		return true;
	}
	return false;
}

void GlCircle::Update( int ticks )
{
	m_tickCount += ticks;
	if( m_tickCount > 100 )
	{
		m_tickCount = 0;
	}
	m_radius += ( m_direction ? 1 : -1 ) * .1f;
	if( m_radius < 0 )
	{
		m_radius = 0;
		m_direction = true;
	}
	if( m_radius > m_startingRadius )
	{
		m_radius = m_startingRadius;
		m_direction = false;
	}
}