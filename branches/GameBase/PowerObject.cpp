#include "PowerObject.h"

#include <windows.h>
#include <gl\gl.h>
#include "GamePiece.h"
#include "GameStructs.h"

#define MOVE_SPEED	0.05
#define LEFT		false
#define RIGHT		true

PowerObject::PowerObject( const Square & startingPos , bool direction , unsigned int leftTextureId , unsigned int rightTextureId )
:	GamePiece( startingPos , ( direction ? rightTextureId : leftTextureId ) ),
	m_direction( direction ),
	m_active( true )
{
}

PowerObject::~PowerObject()
{
}

void PowerObject::Update( int ticks )
{
	if( m_active )
	{
		m_currentLocation.left += (double)ticks * MOVE_SPEED * ( m_direction ? 1 : -1 );
		m_currentLocation.right += (double)ticks * MOVE_SPEED * ( m_direction ? 1 : -1 );
	}
}

void PowerObject::Draw()
{
	if( m_active )
	{
		glEnable( GL_BLEND );
		glDisable( GL_DEPTH_TEST  );
		GamePiece::Draw();
		glEnable( GL_DEPTH_TEST );
		glDisable( GL_BLEND  );
	}
}

bool PowerObject::IsDead()
{
	return !m_active;
}

bool PowerObject::CheckCollision( CollisionObject * object )
{
	GamePiece * currentPiece = NULL;
	if( m_active && ( currentPiece = dynamic_cast<GamePiece *>( object ) ) )
	{
		Square objectPos = currentPiece->GetCurrentPosition();
		if( ( ( m_currentLocation.bottom >= objectPos.bottom && m_currentLocation.bottom <= objectPos.top ) ||
			( m_currentLocation.top >= objectPos.bottom && m_currentLocation.top <= objectPos.top ) ) &&
			( ( m_currentLocation.left >= objectPos.left && m_currentLocation.left <= objectPos.right ) ||
			( m_currentLocation.right >= objectPos.left && m_currentLocation.right <= objectPos.right ) ) )
		{
			currentPiece->Collide( CS_LEFT , 1 );
			Collide( CS_LEFT , 1 );
			return true;
		}
	}
	return false;
}

bool PowerObject::Collide( CollisionSideEnum side , int damage )
{
	if( damage >= 0 )
	{
		m_active = false;
	}
	else if( damage == -1 && ( side == CS_LEFT || side == CS_RIGHT ) )
	{
		m_active = false;
	}
	return false;
}