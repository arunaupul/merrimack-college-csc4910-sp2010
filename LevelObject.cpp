#include "LevelObject.h"
#include "GameDude.h"

#include <windows.h>
#include <gl\gl.h>

#define RIGHT_MOVE_DISTANCE		0.02
#define LEFT_MOVE_DISTANCE		-RIGHT_MOVE_DISTANCE
#define CLIP_DISTANCE			5.0

LevelObject::LevelObject( const std::wstring & levelName)
:	m_levelName( levelName ),
	m_xOffset( 0.0 ),
	m_maxXOffset( 260.0 ),
	m_screenWidth( 800 ),
	m_levelEndObject( NULL )
{
	m_backGroundManager = new BackGroundManager( L"GamePackFiles\\Images\\bg1.tga", 120, 84 , 0.20 );
	m_screenStartIter = m_levelObjects.begin();
	m_screenEndIter = m_levelObjects.end();
}

LevelObject::~LevelObject()
{
}

void LevelObject::Draw()
{
	m_backGroundManager->Draw( m_xOffset );
	glTranslated( -1 * m_xOffset , 0 , 0 );
	for( std::list<GamePiece *>::iterator iter = m_screenStartIter ; iter != m_screenEndIter && iter != m_levelObjects.end() ; ++iter )
	{
		(*iter)->Draw();
	}
	for( std::list<AIObject *>::iterator iter = m_activeAIList.begin() ; iter != m_activeAIList.end() ; ++iter )
	{
		(*iter)->Draw();
	}
	glTranslated( m_xOffset , 0 , 0 );
}

double LevelObject::Move( double distance )
{
	double returnValue = 0.0;
	m_xOffset += distance;
	if( m_xOffset < 0 )
	{
		returnValue = m_xOffset;
		m_xOffset = 0.0;
	}
	else if( m_xOffset > m_maxXOffset )
	{
		returnValue = m_xOffset - m_maxXOffset;
		m_xOffset = m_maxXOffset;
	}
	// Right movement
	if( distance >= 0 )
	{
		while( m_screenStartIter != m_levelObjects.end() && !(*m_screenStartIter)->OnScreen( m_xOffset - CLIP_DISTANCE , m_xOffset + m_screenWidth + CLIP_DISTANCE ) )
		{
			++m_screenStartIter;
		}
		while( m_screenEndIter != m_levelObjects.end() && (*m_screenStartIter)->OnScreen( m_xOffset - CLIP_DISTANCE , m_xOffset + m_screenWidth + CLIP_DISTANCE ) )
		{
			++m_screenEndIter;
		}
		for( std::list<AIObject *>::iterator iter = m_passiveAIList.begin() ; iter != m_passiveAIList.end() ; ++iter )
		{
			if( ( *iter )->Trigger( m_xOffset +  m_screenWidth ) )
			{
				m_activeAIList.push_back( *iter );
			}
		}
	}
	// Left movement
	else
	{
		if( m_screenStartIter == m_levelObjects.end() )
		{
			m_screenStartIter--;
		}
		if( m_screenEndIter == m_levelObjects.end() )
		{
			m_screenEndIter--;
		}
		while( m_screenStartIter != m_levelObjects.begin() && (*m_screenStartIter)->OnScreen( m_xOffset - CLIP_DISTANCE , m_xOffset + m_screenWidth + CLIP_DISTANCE ) )
		{
			--m_screenStartIter;
		}
		while( m_screenEndIter != m_levelObjects.begin() && !(*m_screenEndIter)->OnScreen( m_xOffset - CLIP_DISTANCE , m_xOffset + m_screenWidth + CLIP_DISTANCE ) )
		{
			--m_screenEndIter;
		}
		// After all is said and done, the stop iterator is off by 1 to the left
		// We need to account for this. The above logic should be adjusted to
		// Account for this
		if( m_screenEndIter != m_levelObjects.end() )
		{
			++m_screenEndIter;
		}
	}
	return returnValue;
}

bool LevelObject::Update( int ticks , GameDude * gameDude )
{
	if( gameDude->GetVerticalstatus() == VS_NONE )
	{
		gameDude->SetVerticalStatus( VS_FALLING );
	}
	for( std::list<GamePiece *>::iterator current = m_screenStartIter ; current != m_screenEndIter && current != m_levelObjects.end(); ++current )
	{
		(*current)->CheckCollision( gameDude );
	}
	for( std::list<AIObject *>::iterator currentAI = m_activeAIList.begin() ; currentAI != m_activeAIList.end(); ++currentAI )
	{
		( *currentAI )->SetVerticalStatus( VS_FALLING );
		for( std::list<GamePiece *>::iterator current = m_screenStartIter ; current != m_screenEndIter && current != m_levelObjects.end(); ++current )
		{
			(*current)->CheckCollision( ( *currentAI ) );
		}
	}
	// TODO: Clean up the active AI list
	if( gameDude->GetHorizontalStatus() == HS_RIGHT )
	{
		if( gameDude->Move( ticks * RIGHT_MOVE_DISTANCE ) >= 0.0 )
		{
			Move( ticks * RIGHT_MOVE_DISTANCE );
		}
	}
	else if( gameDude->GetHorizontalStatus() == HS_LEFT )
	{
		if( gameDude->Move( ticks * LEFT_MOVE_DISTANCE ) >= 0.0 )
		{
			Move( ticks * LEFT_MOVE_DISTANCE );
		}
	}
	for( std::list<AIObject *>::iterator current = m_activeAIList.begin() ; current != m_activeAIList.end() ; ++current )
	{
		(*current)->Update( ticks );
	}
	return m_levelEndObject->LevelDone();
}

void LevelObject::AddGamePiece( GamePiece * piece )
{
	if( piece )
	{
		m_levelObjects.push_back( piece );
	}
}

void LevelObject::AddAIObject( AIObject * object )
{
	if( object )
	{
		m_passiveAIList.push_back( object );
	}
}

void LevelObject::Start()
{
	if( !m_levelEndObject )
	{
		m_levelEndObject = new LevelEndObject( Square( -1 , -1 , -1 , -1 ) , -1 );
	}
	m_screenStartIter = m_levelObjects.begin();
	m_screenEndIter = m_screenStartIter;
	while( m_screenStartIter != m_levelObjects.end() && !(*m_screenStartIter)->OnScreen( m_xOffset - CLIP_DISTANCE , m_xOffset + m_screenWidth + CLIP_DISTANCE ) )
	{
		++m_screenStartIter;
	}
	while( m_screenEndIter != m_levelObjects.end() && (*m_screenStartIter)->OnScreen( m_xOffset - CLIP_DISTANCE , m_xOffset + m_screenWidth + CLIP_DISTANCE ) )
	{
		++m_screenEndIter;
	}
	for( std::list<AIObject *>::iterator iter = m_passiveAIList.begin() ; iter != m_passiveAIList.end() ; ++iter )
	{
		if( ( *iter )->Trigger( m_xOffset +  m_screenWidth ) )
		{
			m_activeAIList.push_back( *iter );
		}
	}
}

void LevelObject::SetLevelEndObject( LevelEndObject * object )
{
	m_levelEndObject = object;
}