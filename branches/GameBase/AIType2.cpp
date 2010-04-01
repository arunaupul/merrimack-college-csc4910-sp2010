#include "AIType2.h"
#include "ScoreManager.h"
#include "GameDude.h"

#define TRIGGER_DISTANCE	2
#define LEFT				true
#define RIGHT				false
#define MOVE_DISTANCE		0.005
#define FALL_SPEED			0.03

AIType2::AIType2( const Square & startingPos , unsigned int leftTextureId , unsigned int rightTextureId )
:	AIType1( startingPos , leftTextureId , rightTextureId ),
	m_verticalCollisionsThisPass( 0 )
{
}

AIType2::~AIType2()
{
}

void AIType2::Update( int ticks )
{
	if( m_verticalCollisionsThisPass <= 1 )
	{
		SwitchDirections( !m_direction );
	}
	m_verticalCollisionsThisPass = 0;
	AIType1::Update( ticks );
}

bool AIType2::Collide( CollisionSideEnum side , int damage )
{
	if( side == CS_BOTTOM && damage == -1 )
	{
		m_verticalCollisionsThisPass++;
	}
	return AIType1::Collide( side , damage );
}