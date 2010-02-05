#include "GameTest.h"
#include "GameDude.h"
#include "GameWorld.h"
#include "GameDudeStatusEnum.h"

#include <windows.h>
#include <gl\gl.h>

GameTest::GameTest()
{
}

GameTest::~GameTest()
{
	delete m_dude;
	m_dude = NULL;
	delete m_gameWorld;
	m_gameWorld = NULL;
	m_objectList.clear();
}

bool GameTest::PerformInit()
{
	glEnable( GL_TEXTURE_2D );
	m_dude = new GameDude();
	m_gameWorld = new GameWorld( m_dude );
	m_objectList.push_back( m_gameWorld );
	m_objectList.push_back( m_dude );
	return true;
}

void GameTest::KeyPressed( unsigned int key )
{
	if( key == VK_RIGHT )
	{
		m_dude->SetHorizontalStatus( LEFT );
	}
	if( key == VK_LEFT )
	{
		m_dude->SetHorizontalStatus( RIGHT );
	}
	if( key == VK_UP )
	{
		m_dude->SetVerticalStatus( JUMPING );
	}
	if( key == VK_DOWN )
	{
		m_dude->SetCrouching( true );
	}
}

void GameTest::KeyReleased( unsigned int key )
{
	if( key == VK_RIGHT && m_dude->GetHorizontalStatus() == LEFT )
	{
		m_dude->SetHorizontalStatus( NONE );
	}
	if( key == VK_LEFT && m_dude->GetHorizontalStatus() == RIGHT )
	{
		m_dude->SetHorizontalStatus( NONE );
	}
	if( key == VK_DOWN )
	{
		m_dude->SetCrouching( false );
	}
}

void GameTest::PerformUpdate( int currentTick )
{
	GlApplication::PerformUpdate( currentTick );
}