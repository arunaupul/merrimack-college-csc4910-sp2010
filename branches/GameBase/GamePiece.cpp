#include "GamePiece.h"
#include "GameStructs.h"

#include <windows.h>
#include <gl/gl.h>

#define _ENABLE_BREAKABLE_BLOCKS_

GamePiece::GamePiece( const Square & startingPos , unsigned int textureId )
:	m_currentLocation( startingPos ),
	m_textureId( textureId ),
	m_broken( false )
{
}

void GamePiece::Draw()
{
	if( !m_broken )
	{
		glColor4d( 1.0 , 1.0 , 1.0 , 1.0);
		glBindTexture( GL_TEXTURE_2D , m_textureId );
		glBegin( GL_POLYGON );
			glTexCoord2d( 0 , 1 );
			glVertex3d( m_currentLocation.left , m_currentLocation.top , 0.0 );
			glTexCoord2d( 1 , 1 );
			glVertex3d( m_currentLocation.right , m_currentLocation.top , 0.0 );
			glTexCoord2d( 1 , 0 );
			glVertex3d( m_currentLocation.right , m_currentLocation.bottom , 0.0 );
			glTexCoord2d( 0 , 0 );
			glVertex3d( m_currentLocation.left , m_currentLocation.bottom , 0.0 );
		glEnd();
	}
}

Square GamePiece::GetCurrentPosition()
{
	return m_currentLocation;
}

bool GamePiece::CheckCollision( CollisionObject * object )
{
	if( m_broken )
	{
		return false;
	}
	GamePiece * currentPiece = NULL;
	if( currentPiece = dynamic_cast<GamePiece *>( object ) )
	{
		Square objectPos = currentPiece->GetCurrentPosition();
		if( m_currentLocation.top - objectPos.bottom <= 0.4 &&
			m_currentLocation.top - objectPos.bottom >= -0.4 &&
			( ( m_currentLocation.left <= objectPos.left && m_currentLocation.right >= objectPos.left ) ||
			( m_currentLocation.right >= objectPos.right && m_currentLocation.left <= objectPos.right ) )
			)
		{
			currentPiece->Collide( CS_BOTTOM , -1 );
			Collide( CS_TOP , 0 );
			return true;
		}
		if( m_currentLocation.bottom - objectPos.top <= 0.4 &&
			m_currentLocation.bottom - objectPos.top >= -0.4 &&
			( ( m_currentLocation.left <= objectPos.left && m_currentLocation.right >= objectPos.left ) ||
			( m_currentLocation.right >= objectPos.right && m_currentLocation.left <= objectPos.right ) )
			)
		{
			if( currentPiece->Collide( CS_TOP , -1 ) )
			{
				Collide( CS_BOTTOM , 1 );
			}
			else
			{
				Collide( CS_BOTTOM , 0 );
			}
			return true;
		}
		// Right collision
		if( m_currentLocation.left - objectPos.right <= 0.4 &&
			m_currentLocation.left - objectPos.right >= -0.4 &&
			( ( m_currentLocation.top <= objectPos.top && m_currentLocation.top >= objectPos.bottom ) ||
			( m_currentLocation.bottom >= objectPos.bottom && m_currentLocation.bottom <= objectPos.top ) )
			)
		{
			currentPiece->Collide( CS_RIGHT , -1 );
			Collide( CS_LEFT , 0 );
			return true;
		}
		// Left collision
		if( m_currentLocation.right - objectPos.left <= 0.4 &&
			m_currentLocation.right - objectPos.left >= -0.4 &&
			( ( m_currentLocation.top <= objectPos.top && m_currentLocation.top >= objectPos.bottom ) ||
			( m_currentLocation.bottom >= objectPos.bottom && m_currentLocation.bottom <= objectPos.top ) )
			)
		{
			currentPiece->Collide( CS_LEFT , -1 );
			Collide( CS_RIGHT , 0 );
			return true;
		}
	}
	return false;
}

bool GamePiece::Collide( CollisionSideEnum side , int damage )
{
#ifdef _ENABLE_BREAKABLE_BLOCKS_
	if( side == CS_BOTTOM && damage >= 1 )
	{
		m_broken = true;
	}
#endif
	return false;
}

bool GamePiece::OnScreen( double leftX , double rightX )
{
	return( ( leftX < m_currentLocation.left && rightX > m_currentLocation.left ) ||
		( leftX < m_currentLocation.right && rightX > m_currentLocation.right ) );
}

void GamePiece::SetPosition( const Square & newPos )
{
	m_currentLocation = newPos;
}