#include "GameBase.h"
#include "WorldObject.h"
#include "GraphicLoaders.h"
#include "GameLoader.h"
#include "GameEnums.h"
#include <windows.h>
#include <gl\gl.h>
#include "Converter.h"
#include "ScoreManager.h"
#include "Menu.h"

GameBase::GameBase()
:	m_currentGameState( GS_STARTING_MENU ),
	m_gameDude( NULL ),
	m_menu( NULL )
{
	m_controls = new ControlObject();
	m_controls->LoadControls( L"GamePackFiles\\controls.ini" );
}

GameBase::~GameBase()
{
	KillHudFont();
}

bool GameBase::PerformInit()
{
	glEnable( GL_TEXTURE_2D );
	glColor4d( 1.0 , 1.0 , 1.0 , 1.0 );
	glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

	BuildHUDFont();
	return true;
}

void GameBase::KeyPressed( unsigned int key )
{
	if( m_currentGameState == GS_GAME_PLAYING )
	{
		if( key == m_controls->GetControlKey( CO_RIGHT ) )
		{
			m_gameDude->SetHoriztonalStatus( HS_RIGHT );
		}
		else if( key == m_controls->GetControlKey( CO_LEFT ) )
		{
			m_gameDude->SetHoriztonalStatus( HS_LEFT );
		}
		else if( key == m_controls->GetControlKey( CO_JUMP ) )
		{
			m_gameDude->SetVerticalStatus( VS_JUMPING );
		}
		else if( key == m_controls->GetControlKey( CO_CROUCH ) )
		{
			m_gameDude->SetCrouching( true );
		}
		else if( m_currentGameState == GS_GAME_PLAYING && key == m_controls->GetControlKey( CO_PAUSE ) )
		{
			m_currentGameState = GS_PAUSE_MENU;
		}
	}
	else if( m_currentGameState == GS_STARTING_MENU && m_menu )
	{
		m_menu->HandleKey( key );
	}
}

void GameBase::KeyReleased( unsigned int key )
{
	if( m_currentGameState == GS_GAME_PLAYING )
	{
		if( key == m_controls->GetControlKey( CO_RIGHT ) && m_gameDude->GetHorizontalStatus() == HS_RIGHT )
		{
			m_gameDude->SetHoriztonalStatus( HS_NONE );
		}
		if( key == m_controls->GetControlKey( CO_LEFT ) && m_gameDude->GetHorizontalStatus() == HS_LEFT )
		{
			m_gameDude->SetHoriztonalStatus( HS_NONE );
		}
		if( key == m_controls->GetControlKey( CO_CROUCH ) )
		{
			m_gameDude->SetCrouching( false );
		}
	}
}

void GameBase::PerformUpdate( int currentTick )
{
	switch( m_currentGameState )
	{
		case GS_GAME_PLAYING:
		{
			m_gameDude->Update( currentTick - m_lastTickCount );
			( *m_currentWorld )->Update( currentTick - m_lastTickCount );
			if( m_gameDude->GetDudeStatus() == GDS_DEAD )
			{
				m_currentGameState = GS_PLAYER_DEAD;
				break;
			}
			if( ( *m_currentWorld )->WorldDone() )
			{
				++m_currentWorld;
				if( m_currentWorld == m_worldList.end() )
				{
					m_currentGameState = GS_GAME_CREDITS;
					delete m_gameDude;
					m_gameDude = NULL;
					for( std::list<WorldObject *>::iterator iter = m_worldList.begin() ; iter != m_worldList.end() ; ++iter )
					{
						delete ( *iter );
					}
					m_worldList.clear();
					m_currentWorld = m_worldList.begin();
					m_objectList.clear();
				}
				else
				{
					( *m_currentWorld )->Start();
				}
			}
			break;
		}
		case GS_PLAYER_DEAD:
		{
			( *m_currentWorld )->RestartCurrentLevel();
			m_gameDude->Reset( true );
			m_currentGameState = GS_GAME_PLAYING;
			break;
		}
		case GS_GAME_CREDITS:
		{
			if( true )
			{
				m_currentGameState = GS_STARTING_MENU;
			}
			break;
		}
		case GS_STARTING_MENU:
		{
			if( !m_menu )
			{
				m_menu = new Menu( m_hudTextBase );
				m_menu->AddMenuItem( L"New Game" , SMI_NEW_GAME , Square( 5 , 3 , -2 , 2 ) );
				//m_menu->AddMenuItem( L"Load Game" , SMI_LOAD_GAME , Square( 5 , 3 , -2 , 2 ) );
				m_menu->AddMenuItem( L"Options" , SMI_OPTIONS , Square( 2 , 0 , -2 , 2 ) );
				m_menu->AddMenuItem( L"Quit" , SMI_QUIT , Square( -1 , -3 , -2 , 2 ) );
				m_objectList.push_back( m_menu );
			}
			if( m_menu->GetSelectedItemId() != SMI_INVALID )
			{
				switch( m_menu->GetSelectedItemId() )
				{
					case SMI_NEW_GAME:
					{
						m_currentGameState = GS_GAME_PLAYING;
						PlayGame();
						break;
					}
					case SMI_QUIT:
					{
						m_applicationRunning = false;
						m_currentGameState = GS_QUITING;
						break;
					}
					case SMI_OPTIONS:
					{
						m_currentGameState = GS_OPTIONS_MENU;
						break;
					}
				};
				if( m_currentGameState != GS_STARTING_MENU )
				{
					m_objectList.remove( m_menu );
					delete m_menu;
					m_menu = NULL;
				}
			}
			break;
		}
		case GS_OPTIONS_MENU:
		{
			m_currentGameState = GS_STARTING_MENU;
			break;
		}
		case GS_PAUSE_MENU:
		{
			m_currentGameState = GS_GAME_PLAYING;
			break;
		}
	};
}

void GameBase::LeftMouseClick( Point & clickedPoint )
{
	if( m_menu )
	{
		m_menu->Click( clickedPoint );
	}
}

void GameBase::PlayGame()
{
	unsigned int dudeTextureId = -1;
	unsigned int bigDudeTextureId = -1;
	unsigned int specialDudeTextureId = -1;

	/* Clean up current game if needed */
	if( m_gameDude )
	{
		delete m_gameDude;
		m_gameDude = NULL;
	}
	for( std::list<WorldObject *>::iterator iter = m_worldList.begin() ; iter != m_worldList.end() ; ++iter )
	{
		delete ( *iter );
	}
	m_worldList.clear();
	m_currentWorld = m_worldList.begin();
	m_objectList.clear();

	/* Start Game Setup */
	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\dude.tga" , dudeTextureId );
	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\BigDude.tga" , bigDudeTextureId );
	GraphicLoaders::LoadTga( "GamePackFiles\\Images\\BigDude2.tga" , specialDudeTextureId );
	m_gameDude = new GameDude( Square( SQUARE_SIZE * 2.8 , SQUARE_SIZE * 2 , 120 - ( SQUARE_SIZE * .4 ) , 120.0 + SQUARE_SIZE * .4 ) , dudeTextureId , bigDudeTextureId , specialDudeTextureId );
	GameLoader::RunLoader( L"GamePackFiles\\worlds.ini" , m_worldList , m_gameDude );
	m_currentWorld = m_worldList.begin();
	( *m_currentWorld )->Start();
	m_objectList.push_back( ( *m_currentWorld ) );
	m_objectList.push_back( m_gameDude );
	ScoreManager::Instance()->Reset();
}

void GameBase::BuildHUDFont()
{
	HFONT font;
	m_hudTextBase = glGenLists( 256 );

	font = CreateFont( -12,
						0,
						0,
						0,
						FW_BOLD,
						FALSE,
						FALSE,
						FALSE,
						DEFAULT_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE | DEFAULT_PITCH,
						L"Digital-7");
	SelectObject( m_window , font );
	wglUseFontOutlines( m_window,
						0,
						255,
						m_hudTextBase,
						0.0f,
						0.0f,
						WGL_FONT_POLYGONS,
						m_hudTextGmf);
}
void GameBase::KillHudFont()
{
	glDeleteLists( m_hudTextBase , 256 );
}

void GameBase::Draw()
{
	GlApplication::Draw();

	if( m_currentGameState == GS_GAME_PLAYING )
	{
		glDisable( GL_TEXTURE_2D );
		std::string score = Converter::IntToString( ScoreManager::Instance()->GetCurrentScore() );
		std::wstring timerString = ( *m_currentWorld )->GetTimerString();
		glLoadIdentity();
		glColor3d( 1.0 , 0.0 , 0.0 );
		glTranslated( -10 , 7 , -20 );
		glPushAttrib( GL_LIST_BIT );
		glListBase( m_hudTextBase );
		glCallLists( score.length() , GL_UNSIGNED_BYTE , score.c_str() );
		glPopAttrib();
		glLoadIdentity();
		glTranslated( 8 , 7 , -20 );
		glPushAttrib( GL_LIST_BIT );
		glListBase( m_hudTextBase );
		glCallLists( timerString.length() , GL_UNSIGNED_SHORT , timerString.c_str() );
		glPopAttrib();
		glEnable( GL_TEXTURE_2D );
	}
}