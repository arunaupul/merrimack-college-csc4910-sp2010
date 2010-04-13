#include "GameDude.h"
#include "GameStructs.h"
#include <windows.h>
#include <gl\gl.h>

#define JUMP_HEIGHT SQUARE_SIZE * 2.5
#define JUMP_RATE	0.03

GameDude::GameDude( Square startingPos , unsigned int smallTextureId , unsigned int largeTextureId , unsigned int specialTextureId )
:	GamePiece( startingPos , smallTextureId ),
	m_gameDudeStatus( GDS_SMALL ),
	m_hStatus( HS_NONE ),
	m_vStatus( VS_NONE ),
	m_gameFloor( -8.0 ),
	m_xOffset( 0.0 ),
	m_jumpHeight( 0.0 ),
	m_startingPos( startingPos ),
	m_crouching( false ),
	m_invincible( 0 ),
	m_lastDirection( true )
{
	m_textureIds[0] = smallTextureId;
	m_textureIds[1] = largeTextureId;
	m_textureIds[2] = specialTextureId;
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

VerticalStatus GameDude::GetVerticalStatus()
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
			m_currentLocation.top = m_currentLocation.bottom + m_startingPos.top - m_startingPos.bottom;
			m_textureId = m_textureIds[0];
			break;
		}
		case GDS_BIG:
		{
			m_currentLocation.top = m_currentLocation.bottom + ( ( m_startingPos.top - m_startingPos.bottom )* ( m_crouching ? 1 : 2 ) );
			m_textureId = m_textureIds[1];
			break;
		}
		case GDS_SPECIAL:
		{
			m_currentLocation.top = m_currentLocation.bottom + ( ( m_startingPos.top - m_startingPos.bottom ) * ( m_crouching ? 1 : 2 ) );
			m_textureId = m_textureIds[2];
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
		if( newStatus != HS_NONE )
		{
			m_lastDirection = ( newStatus == HS_LEFT ? false : true );
		}
		m_hStatus = newStatus;
	}
}

void GameDude::Update( int ticks )
{
	if( m_invincible > 0 )
	{
		m_invincible += ticks;
		if( m_invincible >= 5000 )
		{
			m_invincible = 0;
		}
	}
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
	VerticalStatus oldVStatus = m_vStatus;
	if( CS_BOTTOM == side && damage == -1 && m_vStatus != VS_JUMPING )
	{
		m_vStatus = VS_NONE;
	}
	else if( CS_BOTTOM == side && damage == 0 )
	{
		m_vStatus = VS_JUMPING;
	}
	else if( side == CS_LEFT && damage == -1 && m_hStatus == HS_LEFT )
	{
		m_hStatus = HS_NONE;
	}
	else if( side == CS_RIGHT && m_hStatus == HS_RIGHT && damage == -1 )
	{
		m_hStatus = HS_NONE;
	}
	else if( side == CS_TOP && damage == -1 && m_vStatus == VS_JUMPING )
	{
		m_vStatus = VS_NONE;
	}
	else if( damage > 0 && m_invincible == 0.0 )
	{
		if( m_gameDudeStatus - damage < 0 )
		{
			m_gameDudeStatus = GDS_DEAD;
		}
		else
		{
			m_gameDudeStatus = (GameDudeStatus)( m_gameDudeStatus - damage );
			m_invincible += 1;
			SetDudeStatus( m_gameDudeStatus );
		}
	}
	return ( oldVStatus == VS_JUMPING );
}

void GameDude::Draw()
{
	glEnable( GL_BLEND );
	glDisable( GL_DEPTH_TEST );
	if( m_xOffset > 0 )
	{
		glTranslated( -1 * m_xOffset , 0.0 , 0.0 );
	}
	GamePiece::Draw();
	if( m_xOffset > 0 )
	{
		glTranslated( m_xOffset , 0.0 , 0.0 );
	}
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
}

void GameDude::SetLeftBound( double newLeftX )
{
	m_currentLocation.right = newLeftX + m_currentLocation.right - m_currentLocation.left;
	m_currentLocation.left = newLeftX;
}

void GameDude::Reset( bool resetDudeStatus )
{
	m_currentLocation = m_startingPos;
	m_vStatus = VS_NONE;
	m_hStatus = HS_NONE;
	m_xOffset = 0.0;
	m_jumpHeight = 0.0;
	m_textureId = m_textureIds[0];
	if( resetDudeStatus )
	{
		m_gameDudeStatus = GDS_SMALL;
	}
	SetDudeStatus( m_gameDudeStatus );
}

void GameDude::SetCrouching( bool status )
{
	m_crouching = status;
	if( m_gameDudeStatus != GDS_SMALL )
	{
		m_currentLocation.top = m_currentLocation.bottom + ( ( m_startingPos.top - m_startingPos.bottom ) * ( m_crouching ? 1 : 2 ) );
	}
}

bool GameDude::GetFacing()
{
	return m_lastDirection;
}