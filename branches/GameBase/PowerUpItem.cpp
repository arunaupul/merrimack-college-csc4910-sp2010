#include "PowerUpItem.h"
#include "GameStructs.h"
#include "GameDude.h"
#include "GameEnums.h"

#define VERTICAL_RATE	0.01
#define MOVE_RATE		0.01

PowerUpItem::PowerUpItem( const Square & startingPos , unsigned int textureId )
:	AIType1( startingPos , textureId , textureId ),
	m_jumpHeight( 0.0001 ),
	m_triggered( false )
{
}

PowerUpItem::~PowerUpItem()
{
}

void PowerUpItem::Update( int ticks )
{
	if( m_vStatus == VS_JUMPING )
	{
		m_currentLocation.top += (double)ticks * VERTICAL_RATE;
		m_currentLocation.bottom += (double)ticks * VERTICAL_RATE;
		m_jumpHeight += (double)ticks * VERTICAL_RATE;
		if( m_jumpHeight >= SQUARE_SIZE )
		{
			m_jumpHeight = 0.0;
			m_vStatus = VS_NONE;
		}
	}
	else
	{
		AIType1::Update( ticks );
	}
}

bool PowerUpItem::Trigger( double xOffset )
{
	if( m_triggered )
	{
		m_triggered = false;
		return true;
	}
	return false;
}

void PowerUpItem::Activate()
{
	if( !m_killed )
	{
		m_active = true;
		m_triggered = true;
		m_vStatus = VS_JUMPING;
	}
}


bool PowerUpItem::Collide( CollisionSideEnum side , int damage )
{
	if( side == CS_BOTTOM && damage == -1 && m_active && m_jumpHeight == 0.0 )
	{
		m_vStatus = VS_NONE;
	}
	return false;
}

bool PowerUpItem::CheckCollision( CollisionObject * object )
{
	if( !m_active )
	{
		return false;
	}
	GameDude * dude = dynamic_cast<GameDude *>( object );
	if( dude )
	{
		Square dudePos = dude->GetCurrentPosition();
		if( ( ( dudePos.bottom >= m_currentLocation.bottom && dudePos.bottom <= m_currentLocation.top ) ||
			( dudePos.top >= m_currentLocation.bottom && dudePos.top <= m_currentLocation.top ) ) &&
			( ( dudePos.left >= m_currentLocation.left && dudePos.left <= m_currentLocation.right ) ||
			( dudePos.right >= m_currentLocation.left && dudePos.right <= m_currentLocation.right ) ) )
		{
			m_active = false;
			m_killed = true;
			GameDudeStatus status = dude->GetDudeStatus();
			if( status < GDS_SPECIAL )
			{
				dude->SetDudeStatus( (GameDudeStatus)( status + 1 ) );
			}
			return true;
		}
	}
	return false;
}

void PowerUpItem::SetVerticalStatus( VerticalStatus status )
{
	if( m_vStatus != VS_JUMPING && m_active )
	{
		AIType1::SetVerticalStatus( status );
	}
}