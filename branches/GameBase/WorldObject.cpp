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
	(*m_currentLevel)->Start();
}