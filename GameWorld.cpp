#include "GameWorld.h"
#include "TestBlocks.h"
#include "BackGroundManager.h"

#include <windows.h>
#include <gl\gl.h>

GameWorld::GameWorld( GameDude * gameDude )
:	m_currentOffset( 0 ),
	m_screenWidth( 120 ),
	m_worldLength( 480 ),
	m_offScreenDrawDistance( 10 ),
	m_background( new BackGroundManager( L"bg1.bmp" , 120 , 84 , 0.50 ) ),
	m_gameDude( gameDude )
{
	m_worldObjectList.push_back( new TestBlocks( 10 , 13 , 15 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 55 , 13 , 60 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 85 , 13 , 90 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 100 , 13 , 105 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 120 , 13 , 125 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 140 , 13 , 145 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 165 , 13 , 170 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 180 , 13 , 185 , 8 ) );
	m_worldObjectList.push_back( new TestBlocks( 200 , 13 , 205 , 8 ) );
	m_startIter = m_worldObjectList.begin();
	while( m_startIter != m_worldObjectList.end() && !(*m_startIter)->ObjectOnScreen( 0.0 - m_offScreenDrawDistance , m_screenWidth + m_offScreenDrawDistance ) )
	{
		++m_startIter;
	}
	m_stopIter = m_startIter;
	while( m_stopIter != m_worldObjectList.end() && (*m_stopIter)->ObjectOnScreen( 0.0 - m_offScreenDrawDistance , m_screenWidth + m_offScreenDrawDistance ) )
	{
		++m_stopIter;
	}
}

GameWorld::~GameWorld()
{
	for( std::list< WorldObject * >::iterator iter = m_worldObjectList.begin() ; iter != m_worldObjectList.end() ; ++iter )
	{
		delete ( *iter );
	}
}

void GameWorld::Move( double x )
{
	if( m_currentOffset + x < 0 )
	{
		double playerOffset = m_currentOffset + x;
		m_currentOffset = 0;
		m_gameDude->Move( playerOffset );
	}
	else if( m_currentOffset + m_screenWidth + x > m_worldLength )
	{
		double playerOffset = ( m_currentOffset + m_screenWidth + x ) - m_worldLength;
		m_currentOffset = m_worldLength - m_screenWidth;
		m_gameDude->Move( playerOffset );
	}
	else
	{
		if( !m_gameDude->GetXOffset() )
		{
			m_currentOffset += x;

			// Right movement
			if( x >= 0 )
			{
				while( m_startIter != m_worldObjectList.end() && !(*m_startIter)->ObjectOnScreen( m_currentOffset - m_offScreenDrawDistance , m_currentOffset + m_screenWidth + m_offScreenDrawDistance ) )
				{
					++m_startIter;
				}
				while( m_stopIter != m_worldObjectList.end() && (*m_stopIter)->ObjectOnScreen( m_currentOffset - m_offScreenDrawDistance , m_currentOffset + m_screenWidth + m_offScreenDrawDistance ) )
				{
					++m_stopIter;
				}
			}
			// Left movement
			else
			{
				if( m_startIter == m_worldObjectList.end() )
				{
					--m_startIter;
				}
				while( m_startIter != m_worldObjectList.begin() && (*m_startIter)->ObjectOnScreen( m_currentOffset - m_offScreenDrawDistance , m_currentOffset + m_screenWidth + m_offScreenDrawDistance ) )
				{
					--m_startIter;
				}
				if( !(*m_startIter)->ObjectOnScreen( m_currentOffset - m_offScreenDrawDistance , m_currentOffset + m_screenWidth + m_offScreenDrawDistance ) )
				{
					++m_startIter;
				}
			}
		}
		else
		{
			m_gameDude->Move( x );
		}
	}
}

void GameWorld::Draw()
{
	// Iterate through the objectList and call draw on each one
	m_background->Draw( m_currentOffset );
	glTranslated( -1 * m_currentOffset , 0 , 0 );
	for( std::list< WorldObject * >::iterator iter = m_startIter ; iter != m_stopIter ; ++iter )
	{
		( *iter )->Draw();
	}
	glTranslated( m_currentOffset , 0 , 0 );
}

void GameWorld::Update( int ticks )
{
	switch( m_gameDude->GetHorizontalStatus() )
	{
		case STANDING:
			break;
		case RIGHT:
			 Move( ticks * -0.02 );
			break;
		case LEFT:
			 Move( ticks * 0.02 );
			break;
	}
}