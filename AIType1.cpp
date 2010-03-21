#include "AIType1.h"
#include "GameEnums.h"

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
	if( m_active )
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
			m_active = false;
		}
	}
}

bool AIType1::Trigger( double xOffset )
{
	if( !m_active && m_currentLocation.left - xOffset <= TRIGGER_DISTANCE )
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
		else
		{
			// do something
		}
	}
	else if( side == CS_RIGHT && m_direction == RIGHT )
	{
		m_direction = LEFT;
	}
	else if( side == CS_LEFT && m_direction == LEFT )
	{
		m_direction = RIGHT;
	}
	return false;
}