#include "AIType1.h"
#include "GameEnums.h"
#include "GameDude.h"

#define TRIGGER_DISTANCE	50
#define LEFT				true
#define RIGHT				false
#define MOVE_DISTANCE		0.005
#define FALL_SPEED			0.02

AIType1::AIType1( const Square & startingPos , unsigned int textureId )
:	AIObject( startingPos , textureId ),
	m_direction( LEFT )
{
}

AIType1::~AIType1()
{
}

void AIType1::Update( int ticks )
{
	if( m_active && !m_killed )
	{
		if( m_vStatus == VS_NONE )
		{
			m_currentLocation.left += (double)ticks * MOVE_DISTANCE * ( m_direction ? -1.0 : 1.0 );
			m_currentLocation.right += (double)ticks * MOVE_DISTANCE * ( m_direction ? -1.0 : 1.0 );
		}
		if( m_vStatus == VS_FALLING )
		{
			m_currentLocation.top -= (double)ticks * FALL_SPEED;
			m_currentLocation.bottom -= (double)ticks * FALL_SPEED;
		}
		if( m_currentLocation.bottom < m_gameFloor )
		{
			m_killed = true;
		}
	}
}

bool AIType1::Trigger( double xOffset )
{
	if( !m_active && !m_killed && m_currentLocation.left - xOffset <= TRIGGER_DISTANCE )
	{
		m_active = true;
		return true;
	}
	return false;
}

bool AIType1::Collide( CollisionSideEnum side , int damage )
{
	if( side == CS_BOTTOM )
	{
		if( damage == -1 )
		{
			m_vStatus = VS_NONE;
		}
	}
	else if( side == CS_RIGHT && m_direction == RIGHT && damage == -1 )
	{
		m_direction = LEFT;
	}
	else if( side == CS_LEFT && m_direction == LEFT && damage == -1 )
	{
		m_direction = RIGHT;
	}
	else if( side == CS_TOP && damage > 0 )
	{
		m_killed = true;
	}
	return false;
}

bool AIType1::CheckCollision( CollisionObject * object )
{
	if( !m_active || m_killed )
	{
		return false;
	}
	GameDude * gameDude = 0;
	if( gameDude = dynamic_cast<GameDude *>( object ) )
	{
		Square objectPos = gameDude->GetCurrentPosition();
		if( m_currentLocation.top - objectPos.bottom <= 0.1 &&
			m_currentLocation.top - objectPos.bottom >= -0.2 &&
			( ( m_currentLocation.left <= objectPos.left && m_currentLocation.right >= objectPos.left ) ||
			( m_currentLocation.right >= objectPos.right && m_currentLocation.left <= objectPos.right ) )
			)
		{
			if( gameDude->GetVerticalStatus() == VS_FALLING )
			{
				gameDude->Collide( CS_BOTTOM , 0 );
				Collide( CS_TOP , 1 );
			}
			else
			{
				gameDude->Collide( CS_BOTTOM , 1 );
				Collide( CS_TOP , 0 );
			}
			return true;
		}
		if( m_currentLocation.bottom - objectPos.top <= 0.1 &&
			m_currentLocation.bottom - objectPos.top >= -0.2 &&
			( ( m_currentLocation.left <= objectPos.left && m_currentLocation.right >= objectPos.left ) ||
			( m_currentLocation.right >= objectPos.right && m_currentLocation.left <= objectPos.right ) )
			)
		{
			gameDude->Collide( CS_TOP , 1 );
			Collide( CS_BOTTOM , 0 );
			return true;
		}
		// Right collision
		if( m_currentLocation.left - objectPos.right <= 0.1 &&
			m_currentLocation.left - objectPos.right >= -0.1 &&
			( ( m_currentLocation.top <= objectPos.top && m_currentLocation.top >= objectPos.bottom ) ||
			( m_currentLocation.bottom >= objectPos.bottom && m_currentLocation.bottom <= objectPos.top ) )
			)
		{
			//gameDude->Collide( CS_RIGHT , 1 );
			//Collide( CS_LEFT , 0 );
			return true;
		}
		// Left collision
		if( m_currentLocation.right - objectPos.left <= 0.1 &&
			m_currentLocation.right - objectPos.left >= -0.1 &&
			( ( m_currentLocation.top <= objectPos.top && m_currentLocation.top >= objectPos.bottom ) ||
			( m_currentLocation.bottom >= objectPos.bottom && m_currentLocation.bottom <= objectPos.top ) )
			)
		{
			//gameDude->Collide( CS_LEFT , 1 );
			//Collide( CS_RIGHT , 0 );
			return true;
		}
	}
	return false;
}