#include "LevelEndObject.h"
#include "GameDude.h"
#include "ScoreManager.h"
#include "GameEnums.h"
#include "AudioManager.h"

#include <windows.h>
#include <gl\gl.h>

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
	if( dude && !m_levelDone )
	{
		Square dudePos = dude->GetCurrentPosition();
		if( ( ( dudePos.bottom >= m_currentLocation.bottom && dudePos.bottom <= m_currentLocation.top ) ||
			( dudePos.top >= m_currentLocation.bottom && dudePos.top <= m_currentLocation.top ) ) &&
			( ( dudePos.left >= m_currentLocation.left && dudePos.left <= m_currentLocation.right ) ||
			( dudePos.right >= m_currentLocation.left && dudePos.right <= m_currentLocation.right ) ) )
		{
			m_levelDone = true;
			ScoreManager::Instance()->AddToScore( 100 , SO_LEVEL_END );
			AudioManager::Instance()->PlayALSource( SL_CHCKPT );
			return true;
		}
	}
	return false;
}

void LevelEndObject::Draw()
{
	glEnable( GL_BLEND );
	glDisable( GL_DEPTH_TEST );
	GamePiece::Draw();
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
}