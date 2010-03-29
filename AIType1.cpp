#include "AIType1.h"
#include "GameEnums.h"
#include "GameDude.h"
#include "ScoreManager.h"

#define TRIGGER_DISTANCE	2
#define LEFT				true
#define RIGHT				false
#define MOVE_DISTANCE		0.005
#define FALL_SPEED			0.03

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
	else if( side == CS_TOP && damage > 0 && !m_killed )
	{
		m_killed = true;
		ScoreManager::Instance()->AddToScore( 15 , SO_AI_TYPE_1 );
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
		if( m_currentLocation.top - objectPos.bottom <= 0.5 &&
			m_currentLocation.top - objectPos.bottom >= -0.5 &&
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
		else if( ( ( objectPos.bottom >= m_currentLocation.bottom && objectPos.bottom <= m_currentLocation.top ) ||
			( objectPos.top >= m_currentLocation.bottom && objectPos.top <= m_currentLocation.top ) ) &&
			( ( objectPos.left >= m_currentLocation.left && objectPos.left <= m_currentLocation.right ) ||
			( objectPos.right >= m_currentLocation.left && objectPos.right <= m_currentLocation.right ) ) )
		{
			gameDude->Collide( CS_TOP , 1 );
		}
	}
	return false;
}