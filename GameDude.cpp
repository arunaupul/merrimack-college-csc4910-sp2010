#include "GameDude.h"
#include "GameStructs.h"
#include <windows.h>
#include <gl\gl.h>

#define JUMP_HEIGHT 10.0
#define JUMP_RATE	0.03

GameDude::GameDude( Square startingPos , unsigned int textureId )
:	GamePiece( startingPos , textureId ),
	m_gameDudeStatus( GDS_SMALL ),
	m_hStatus( HS_NONE ),
	m_vStatus( VS_JUMPING ),
	m_gameFloor( 0.0 ),
	m_xOffset( 0.0 ),
	m_jumpHeight( 0.0 )
{
}

GameDude::~GameDude()
{
}

GameDudeStatus GameDude::GetDudeStatus()
{
	return m_gameDudeStatus;
}

HoriztonalStatus GameDude::GetHorizontalStatus()
{
	return m_hStatus;
}

VerticalStatus GameDude::GetVerticalstatus()
{
	return m_vStatus;
}

double GameDude::Move( double x )
{
	m_currentLocation.left += x;
	m_currentLocation.right += x;
	m_xOffset += x;
	return m_xOffset;
}

void GameDude::SetDudeStatus( GameDudeStatus newStatus )
{
	m_gameDudeStatus = newStatus;
	switch( newStatus )
	{
		case GDS_DEAD:
		{
			break;
		}
		case GDS_SMALL:
		{
			break;
		}
		case GDS_BIG:
		{
			break;
		}
		case GDS_SPECIAL:
		{
			break;
		}
		default:
			break;
	};
}

void GameDude::SetVerticalStatus( VerticalStatus newStatus )
{
	if( newStatus != VS_JUMPING )
	{
		m_vStatus = newStatus;
	}
	else if( m_vStatus == VS_NONE )
	{
		m_vStatus = newStatus;
		m_jumpHeight = 0.0;
	}
}

void GameDude::SetHoriztonalStatus( HoriztonalStatus newStatus )
{
	//if( m_vStatus == VS_NONE )
	{
		m_hStatus = newStatus;
	}
}

void GameDude::Update( int ticks )
{
	ticks /= 1.5;
	switch( m_vStatus )
	{
		case VS_FALLING:
		{
			m_currentLocation.top -= (double)(ticks) * JUMP_RATE;
			m_currentLocation.bottom -= (double)(ticks) * JUMP_RATE;
			if( m_currentLocation.top <= m_gameFloor )
			{
				m_gameDudeStatus = GDS_DEAD;
			}
			break;
		}
		case VS_JUMPING:
		{
			if( m_jumpHeight > JUMP_HEIGHT )
			{
				m_jumpHeight = 0.0;
				m_vStatus = VS_FALLING;
			}
			else
			{
				m_jumpHeight += (double)(ticks) * JUMP_RATE;
				m_currentLocation.top += (double)(ticks) * JUMP_RATE;
				m_currentLocation.bottom += (double)(ticks) * JUMP_RATE;
			}
			break;
		}
		default:
			break;
	};
}

bool GameDude::Collide( CollisionSideEnum side , int damage )
{
	if( CS_BOTTOM == side )
	{
		if( damage == -1 && m_vStatus != VS_JUMPING )
		{
			m_vStatus = VS_NONE;
		}
		else
		{
			// m_gameDudeStatus -= damage;
		}
	}
	if( side == CS_LEFT )
	{
		if( damage == -1 && m_hStatus == HS_LEFT )
		{
			m_hStatus = HS_NONE;
		}
	}
	if( side == CS_RIGHT && m_hStatus == HS_RIGHT  )
	{
		if( damage == -1 )
		{
			m_hStatus = HS_NONE;
		}
	}
	if( side == CS_TOP )
	{
		if( damage == -1 && m_vStatus == VS_JUMPING )
		{
			m_vStatus = VS_NONE;
		}
	}
	return false;
}

void GameDude::Draw()
{
	if( m_xOffset > 0 )
	{
		glTranslated( -1 * m_xOffset , 0.0 , 0.0 );
	}
	GamePiece::Draw();
	if( m_xOffset > 0 )
	{
		glTranslated( m_xOffset , 0.0 , 0.0 );
	}
}

void GameDude::SetLeftBound( double newLeftX )
{
	m_currentLocation.right = newLeftX + m_currentLocation.right - m_currentLocation.left;
	m_currentLocation.right = newLeftX;
}