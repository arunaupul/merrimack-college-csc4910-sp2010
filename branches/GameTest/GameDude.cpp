#include "GameDude.h"
#include <windows.h>
#include <gl\gl.h>

#include "GraphicLoaders.h"

GameDude::GameDude()
:	m_jumpHeight( 0.0 ),
	m_crouching( false ),
	m_xOffset( 0 ),
	m_hStatus( NONE ),
	m_vStatus( STANDING )
{
	m_point.x = 60.0;
	m_point.y = 8.0;
	m_point.z = 0;
	GraphicLoaders::LoadNewBitmap( L"dude.bmp" , m_textureId );
}

GameDude::~GameDude()
{
}

void GameDude::Draw()
{
	glColor3d( 1.0 , 1.0 , 1.0 );

	glBindTexture( GL_TEXTURE_2D , m_textureId );
	glBegin( GL_POLYGON );
		glTexCoord2d( 1 , 1 );
		glVertex3d( m_point.x + 1.0 + m_xOffset , m_point.y + ( m_crouching ? 2.0 : 3.0 ) , m_point.z );
		glTexCoord2d( 1 , 0 );
		glVertex3d( m_point.x + 1.0 + m_xOffset , m_point.y , m_point.z );
		glTexCoord2d( 0 , 0 );
		glVertex3d( m_point.x - 1.0 + m_xOffset , m_point.y , m_point.z );
		glTexCoord2d( 0 , 1 );
		glVertex3d( m_point.x - 1.0 + m_xOffset , m_point.y + ( m_crouching ? 2.0 : 3.0 ) , m_point.z );
	glEnd();
}

void GameDude::Update( int ticks )
{
}


Point GameDude::GetCenterPoint()
{
	return m_point;
}

void GameDude::SetCrouching( bool status )
{
	m_crouching = status;
}

double GameDude::GetXOffset()
{
	return m_xOffset;
}

void GameDude::Move( double x )
{
	if( m_xOffset * ( m_xOffset + x ) < 0 )
	{
		m_xOffset = 0;
	}
	else
	{
		m_xOffset += x;
	}
}

void GameDude::SetVerticalStatus( GameDudeVerticalStatus status )
{
	m_vStatus = status;
}

void GameDude::SetHorizontalStatus( GameDudeHorizontalStatus status )
{
	m_hStatus = status;
}

GameDudeVerticalStatus GameDude::GetVerticalStatus()
{
	return m_vStatus;
}

GameDudeHorizontalStatus GameDude::GetHorizontalStatus()
{
	return m_hStatus;
}

Point GameDude::GetTopLeftPoint()
{
	return Point( m_point.x + m_xOffset , m_point.y + ( m_crouching ? 2.0 : 3.0 ) , m_point.z );
}

Point GameDude::GetBottomRightPoint()
{
	return ( m_point.x + m_xOffset + 1 , m_point.y , m_point.z );
}