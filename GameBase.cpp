#include "GameBase.h"
#include "WorldObject.h"
#include "GraphicLoaders.h"
#include "GameLoader.h"
#include "GameEnums.h"
#include <windows.h>
#include <gl\gl.h>

GameBase::GameBase()
:	m_currentGameState( GS_STARTING_MENU )
{
}

GameBase::~GameBase()
{
}

bool GameBase::PerformInit()
{
	glEnable( GL_TEXTURE_2D );
	glColor4d( 1.0 , 1.0 , 1.0 , 0.5 );			// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc( GL_SRC_ALPHA , GL_ONE );
	return true;
}

void GameBase::KeyPressed( unsigned int key )
{
	switch( key )
	{
		case VK_RIGHT:
		{
			m_gameDude->SetHoriztonalStatus( HS_RIGHT );
			break;
		}
		case VK_LEFT:
		{
			m_gameDude->SetHoriztonalStatus( HS_LEFT );
			break;
		}
		case VK_UP:
		case VK_SPACE:
		{
			m_gameDude->SetVerticalStatus( VS_JUMPING );
			break;
		}
	};
}

void GameBase::KeyReleased( unsigned int key )
{
	switch( key )
	{
		case VK_RIGHT:
		{
			if( m_currentGameState == GS_GAME_PLAYING && m_gameDude->GetHorizontalStatus() == HS_RIGHT )
			{
				m_gameDude->SetHoriztonalStatus( HS_NONE );
			}
			break;
		}
		case VK_LEFT:
		{
			if( m_currentGameState == GS_GAME_PLAYING && m_gameDude->GetHorizontalStatus() == HS_LEFT )
			{
				m_gameDude->SetHoriztonalStatus( HS_NONE );
			}
			break;
		}
	};
}

void GameBase::PerformUpdate( int currentTick )
{
	switch( m_currentGameState )
	{
		case GS_GAME_PLAYING:
		{
			m_gameDude->Update( currentTick - m_lastTickCount );
			( *m_currentWorld )->Update( currentTick - m_lastTickCount );
			if( ( *m_currentWorld )->WorldDone() )
			{
				++m_currentWorld;
				if( m_currentWorld == m_worldList.end() )
				{
					m_currentGameState = GS_GAME_CREDITS;
					delete m_gameDude;
					for( std::list<WorldObject *>::iterator iter = m_worldList.begin() ; iter != m_worldList.end() ; ++iter )
					{
						delete ( *iter );
					}
					m_worldList.clear();
					m_currentWorld = m_worldList.begin();
					m_objectList.clear();
					m_gameDude = NULL;
				}
			}
			break;
		}
		case GS_GAME_CREDITS:
		case GS_STARTING_MENU:
		{
			m_currentGameState = GS_GAME_PLAYING;
			PlayGame();
			break;
		}
	};
}

void GameBase::PlayGame()
{
	unsigned int dudeTextureId = -1;
	if( !GraphicLoaders::LoadTga( "GamePackFiles\\Images\\dude.tga" , dudeTextureId ) )
	{
		return ;
	}
	m_gameDude = new GameDude( Square( SQUARE_SIZE * 3 , SQUARE_SIZE * 2 , 58.0 , 62.0 ) , dudeTextureId );
	GameLoader::RunLoader( L"GamePackFiles\\worlds.ini" , m_worldList , m_gameDude );
	m_currentWorld = m_worldList.begin();
	( *m_currentWorld )->Start();
	m_objectList.push_back( ( *m_currentWorld ) );
	m_objectList.push_back( m_gameDude );
}