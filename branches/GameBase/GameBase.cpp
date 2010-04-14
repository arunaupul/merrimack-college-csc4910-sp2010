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
#include "AudioManager.h"

#define FIRE_DELAY	1000

GameBase::GameBase()
:	m_currentGameState( GS_STARTING_MENU ),
	m_gameDude( NULL ),
	m_menu( NULL ),
	m_delayTimer( 0 )
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
		else if( key == m_controls->GetControlKey( CO_PAUSE ) )
		{
			m_currentGameState = GS_PAUSE_MENU;
			AudioManager::Instance()->HoldALSource( SL_SONG1 );
		}
		else if( key == m_controls->GetControlKey( CO_USE_SPECIAL ) && m_gameDude->GetDudeStatus() == GDS_SPECIAL && m_delayTimer == 0 )
		{
			m_delayTimer = 1;
			Square specialSquare = m_gameDude->GetCurrentPosition();
			specialSquare.bottom = specialSquare.top - SQUARE_SIZE * .8;
			(*m_currentWorld)->FireSpecialPower( specialSquare , m_gameDude->GetFacing() );
		}
		if( m_keys.GetPressed( 'D' ) && m_keys.GetPressed( 'B' ) && m_keys.GetPressed( 'Z' ) )
		{
			m_gameDude->SetDudeStatus( GDS_SPECIAL );
		}
	}
	else if( m_currentGameState == GS_STARTING_MENU && m_menu )
	{
		m_menu->HandleKey( key );
	}
	else if( m_currentGameState == GS_PAUSE_MENU )
	{
		if( key == m_controls->GetControlKey( CO_PAUSE ) )
		{
			m_currentGameState = GS_GAME_PLAYING;
			AudioManager::Instance()->PlayALSource( SL_SONG1 );
			// Prevent the controls from sticking on unpause
			if( m_keys.GetPressed( m_controls->GetControlKey( CO_LEFT ) ) )
			{
				m_gameDude->SetHoriztonalStatus( HS_LEFT );
			}
			else if( m_keys.GetPressed( m_controls->GetControlKey( CO_RIGHT ) ) )
			{
				m_gameDude->SetHoriztonalStatus( HS_RIGHT );
			}
			else
			{
				m_gameDude->SetHoriztonalStatus( HS_NONE );
			}
		}
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
	if( m_delayTimer > 0 )
	{
		m_delayTimer += currentTick - m_lastTickCount;
	}
	if( m_delayTimer >= FIRE_DELAY )
	{
		m_delayTimer = 0;
	}
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
			m_gameDude->Reset( true );
			( *m_currentWorld )->RestartCurrentLevel();
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
	AddFontResource( L"GamePackFiles\\Fonts\\digital-7.ttf" );			//uses windows library to add the font digital-7
	//SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);
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
	RemoveFontResource( L"GamePackFiles\\Fonts\\digital-7.ttf" );		//removes the font when done
	//SendMessage(HWND_BROADCAST, WM_FONTCHANGE, 0, 0);					//alert other windows of the change
}

void GameBase::Draw()
{
	GlApplication::Draw();

	if( m_currentGameState == GS_GAME_PLAYING && !( *m_currentWorld )->IsLoading() )
	{
		double centerOffset = 0;
		glDisable( GL_TEXTURE_2D );
		std::string score = Converter::IntToString( ScoreManager::Instance()->GetCurrentScore() );
		std::wstring timerString = ( *m_currentWorld )->GetTimerString();
		std::wstring worldString = ( *m_currentWorld )->GetNameString();

		for( unsigned int x = 0 ; x < worldString.length() / 2 ; x++ )
		{
			centerOffset += m_hudTextGmf[worldString[x]].gmfCellIncX;
		}

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
		glLoadIdentity();
		glTranslated( -1 * centerOffset , 7 , -20 );
		glPushAttrib( GL_LIST_BIT );
		glListBase( m_hudTextBase );
		glCallLists( worldString.length() , GL_UNSIGNED_SHORT , worldString.c_str() );
		glPopAttrib();
		glEnable( GL_TEXTURE_2D );
	}
	else if( m_currentGameState == GS_PAUSE_MENU )
	{
		glDisable( GL_TEXTURE_2D );
		glColor3d( 1.0 , 0.0 , 0.0 );
		glLoadIdentity();
		glTranslated( -1.5 , 0 , -20 );
		glPushAttrib( GL_LIST_BIT );
		glListBase( m_hudTextBase );
		glCallLists( 6 , GL_UNSIGNED_SHORT , L"PAUSED" );
		glPopAttrib();
		glEnable( GL_TEXTURE_2D );
	}
}