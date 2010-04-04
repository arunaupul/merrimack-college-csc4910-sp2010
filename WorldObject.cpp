#include "WorldObject.h"
#include "GameDude.h"

WorldObject::WorldObject( const std::wstring & name , GameDude * dude )
:	m_gameDude( dude ),
	m_worldName( name )
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
	if( (*m_currentLevel)->Update( ticks , m_gameDude ) )
	{
		++m_currentLevel;
		if( m_currentLevel != m_levelList.end() )
		{
			( *m_currentLevel )->Load();
			( *m_currentLevel )->Start();
			m_gameDude->Reset( false );
		}
	}
}

void WorldObject::Draw()
{
	(*m_currentLevel)->Draw();
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
	( *m_currentLevel )->Load();
	( *m_currentLevel )->Start();
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
	if( !( *m_currentLevel )->Reload() )
	{
		return false;
	}
	( *m_currentLevel )->Start();
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