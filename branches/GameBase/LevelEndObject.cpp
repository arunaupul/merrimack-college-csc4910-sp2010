#include "LevelEndObject.h"
#include "GameDude.h"

LevelEndObject::LevelEndObject( Square startingPos , unsigned int textureId )
:	GamePiece( startingPos , textureId ),
	m_levelDone( false )
{
}

LevelEndObject::~LevelEndObject()
{
}

bool LevelEndObject::LevelDone()
{
	return m_levelDone;
}

bool LevelEndObject::CheckCollision( CollisionObject * object )
{
	GameDude * dude = dynamic_cast<GameDude *>( object );
	if( dude )
	{
		Square dudePos = dude->GetCurrentPosition();
		if( ( ( dudePos.bottom >= m_currentLocation.bottom && dudePos.bottom <= m_currentLocation.top ) ||
			( dudePos.top >= m_currentLocation.bottom && dudePos.top <= m_currentLocation.top ) ) &&
			( ( dudePos.left >= m_currentLocation.left && dudePos.left <= m_currentLocation.right ) ||
			( dudePos.right >= m_currentLocation.left && dudePos.right <= m_currentLocation.right ) ) )
		{
			m_levelDone = true;
			return true;
		}
	}
	return false;
}