#include "WorldObject.h"
#include "GameDude.h"

#include <windows.h>
#include <gl\gl.h>

#include "GraphicLoaders.h"

WorldObject::WorldObject( const std::wstring & name , GameDude * dude )
:	m_gameDude( dude ),
	m_worldName( name ),
	m_loadingScreenTextureId( -1 ),
	m_reloadingScreenTextureId( -1 ),
	m_loadingLevel( false ),
	m_firstLoad( false ),
	m_reloading( false )
{
	m_currentLevel = m_levelList.begin();
}

WorldObject::~WorldObject()
{
}

double WorldObject::Move( double distance )
{
	return (*m_currentLevel)->Move( distance );
}

void WorldObject::Update( int ticks )
{
	bool oldLoadingLevel = m_loadingLevel;
	if( !m_firstLoad && ( m_loadingLevel = (*m_currentLevel)->Update( ticks , m_gameDude ) ) )
	{
		m_gameDude->SetPosition( Square( -1.0 , -1.0 , -1.0 , -1.0 ) );
	}
	if( oldLoadingLevel )
	{
		if( !m_firstLoad && !m_reloading )
		{
			++m_currentLevel;
		}
		if( m_currentLevel != m_levelList.end() )
		{
			if( m_reloading )
			{
				( *m_currentLevel )->Reload();
			}
			else
			{
				( *m_currentLevel )->Load();
			}
			( *m_currentLevel )->Start();
			m_gameDude->Reset( m_reloading );
		}
		m_firstLoad = false;
		m_reloading = false;
		m_loadingLevel = false;
	}
}

void WorldObject::Draw()
{
	if( m_loadingLevel )
	{
		if( m_loadingScreenTextureId == -1 )
		{
			GraphicLoaders::LoadTga( ( *m_currentLevel )->GetImageFolder() + L"\\LoadLevel.tga" , m_loadingScreenTextureId );
			GraphicLoaders::LoadTga( ( *m_currentLevel )->GetImageFolder() + L"\\ReloadLevel.tga" , m_reloadingScreenTextureId );
		}
		if( m_reloading )
		{
			glBindTexture( GL_TEXTURE_2D , m_reloadingScreenTextureId );
		}
		else
		{
			glBindTexture( GL_TEXTURE_2D , m_loadingScreenTextureId );
		}
		glColor3d( 1.0 , 0.0 , 0.0 );
		glBegin( GL_POLYGON );
			glTexCoord2d( 0.0 , 0.0 );
			glVertex3d( 0.0 , 0.0 , 0.0 );
			glTexCoord2d( 0.0 , 1.0 );
			glVertex3d( 0.0 , 168.0 , 0.0 );
			glTexCoord2d( 1.0 , 1.0 );
			glVertex3d( 240.0 , 168.0 , 0.0 );
			glTexCoord2d( 1.0 , 0.0 );
			glVertex3d( 240.0 , 0.0 , 0.0 );
		glEnd();
	}
	else
	{
		(*m_currentLevel)->Draw();
	}
}

void WorldObject::AddLevel( LevelObject * level )
{
	if( level )
	{
		m_levelList.push_back( level );
	}
}
void WorldObject::Start()
{
	m_currentLevel = m_levelList.begin();
	m_loadingLevel = true;
	m_firstLoad = true;
	m_gameDude->SetPosition( Square( -1.0 , -1.0 , -1.0 , -1.0 ) );
}

bool WorldObject::WorldDone()
{
	return m_currentLevel == m_levelList.end();
}

void WorldObject::SetWorldName( const std::wstring & name )
{
	m_worldName = name;
}

bool WorldObject::RestartCurrentLevel()
{
	m_loadingLevel = true;
	m_reloading = true;
	m_gameDude->SetPosition( Square( -1.0 , -1.0 , -1.0 , -1.0 ) );
	return true;
}

std::wstring WorldObject::GetTimerString()
{
	return ( *m_currentLevel )->GetTimerString();
}

void WorldObject::FireSpecialPower( Square startingPos , bool direction )
{
	( *m_currentLevel )->FireSpecialPower( startingPos , direction );
}

bool WorldObject::IsLoading()
{
	return m_loadingLevel;
}

std::wstring WorldObject::GetNameString()
{
	return m_worldName + L" - " + ( *m_currentLevel )->GetLevelName();
}