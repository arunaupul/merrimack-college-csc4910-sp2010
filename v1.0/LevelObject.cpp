#include "LevelObject.h"
#include "GameDude.h"
#include "GameLoader.h"
#include "ScoreManager.h"
#include "Converter.h"
#include "PowerObject.h"

#include <windows.h>
#include <gl\gl.h>

#define RIGHT_MOVE_DISTANCE		0.035
#define LEFT_MOVE_DISTANCE		-RIGHT_MOVE_DISTANCE
#define CLIP_DISTANCE			5.0

LevelObject::LevelObject( const std::wstring & levelName)
:	m_levelName( levelName ),
	m_xOffset( 0.0 ),
	m_maxXOffset( 10000.0 ),
	m_screenWidth( 800 ),
	m_levelEndObject( NULL ),
	m_levelFileName( L"" ),
	m_backGroundManager( NULL ),
	m_timer( 0 ),
	m_imageFolder( L"Images" )
{
	m_screenStartIter = m_levelObjects.begin();
	m_screenEndIter = m_levelObjects.end();
	m_specialTextureIds[0] = -1;
	m_specialTextureIds[1] = -1;
}

LevelObject::~LevelObject()
{
	delete m_backGroundManager;
	for( std::list<GamePiece *>::iterator iter = m_levelObjects.begin() ; iter != m_levelObjects.end() ; ++iter )
	{
		delete (*iter);
	}
	m_levelObjects.clear();
	for( std::list<AIObject *>::iterator iter = m_passiveAIList.begin() ; iter != m_passiveAIList.end() ; ++iter )
	{
		delete (*iter);
	}
	m_passiveAIList.clear();
	m_activeAIList.clear();
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
	for( std::list<PowerObject *>::iterator iter = m_powerList.begin() ; iter != m_powerList.end() ; ++iter )
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
	m_timer -= ticks;
	if( m_timer <= 0 )
	{
		gameDude->SetDudeStatus( GDS_DEAD );
	}
	if( gameDude->GetVerticalStatus() == VS_NONE )
	{
		gameDude->SetVerticalStatus( VS_FALLING );
	}
	for( std::list<GamePiece *>::iterator current = m_screenStartIter ; current != m_screenEndIter && current != m_levelObjects.end(); ++current )
	{
		(*current)->CheckCollision( gameDude );
	}
	for( std::list<AIObject *>::iterator iter = m_passiveAIList.begin() ; iter != m_passiveAIList.end() ; )
	{
		if( ( *iter )->Trigger( m_xOffset +  m_screenWidth ) )
		{
			m_activeAIList.push_back( *iter );
			iter = m_passiveAIList.erase( iter );
		}
		else
		{
			++iter;
		}
	}
	for( std::list<AIObject *>::iterator currentAI = m_activeAIList.begin() ; currentAI != m_activeAIList.end(); ++currentAI )
	{
		( *currentAI )->SetVerticalStatus( VS_FALLING );
		for( std::list<GamePiece *>::iterator current = m_screenStartIter ; current != m_screenEndIter && current != m_levelObjects.end(); ++current )
		{
			(*current)->CheckCollision( ( *currentAI ) );
		}
	}
	for( std::list<AIObject *>::iterator currentAI = m_activeAIList.begin() ; currentAI != m_activeAIList.end(); ++currentAI)
	{
		(*currentAI)->CheckCollision( gameDude );
	}
	for( std::list<PowerObject *>::iterator iter = m_powerList.begin() ; iter != m_powerList.end(); )
	{
		bool collide = false;
		for( std::list<AIObject *>::iterator currentAI = m_activeAIList.begin() ; currentAI != m_activeAIList.end(); ++currentAI)
		{
			if( (*currentAI)->GetActiveStatus() && (*iter)->CheckCollision( *currentAI ) )
			{
				iter = m_powerList.erase( iter );
				collide = true;
				break;
			}
		}
		if( !collide )
		{
			for( std::list<GamePiece *>::iterator current = m_screenStartIter ; current != m_screenEndIter && current != m_levelObjects.end(); ++current )
			{
				if( (*iter)->CheckCollision( *current ) )
				{
					iter = m_powerList.erase( iter );
					collide = true;
					break;
				}
			}
		}
		if( !collide )
		{
			++iter;
		}
	}
	for( std::list<AIObject *>::iterator iter = m_activeAIList.begin() ; iter != m_activeAIList.end() ; )
	{
		if( !( *iter )->GetActiveStatus() )
		{
			iter = m_activeAIList.erase( iter );
		}
		else
		{
			++iter;
		}
	}
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
	for( std::list<PowerObject *>::iterator current = m_powerList.begin() ; current != m_powerList.end() ; ++current )
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
	m_timer = 1000 * 5 * 60;
	ScoreManager::Instance()->NewLevel();
}

void LevelObject::SetLevelEndObject( LevelEndObject * object )
{
	m_levelEndObject = object;
}

void LevelObject::SetLevelFileName( const std::wstring & levelFileName )
{
	m_levelFileName = levelFileName;
}

bool LevelObject::Load()
{
	if( m_backGroundManager )
	{
		delete m_backGroundManager;
		m_backGroundManager = NULL;
	}
	m_backGroundManager = new BackGroundManager( m_imageFolder + L"\\bg.bmp", 240, 168 , 0.20 );
	for( std::list<GamePiece *>::iterator iter = m_levelObjects.begin() ; iter != m_levelObjects.end() ; ++iter )
	{
		delete (*iter);
	}
	m_levelObjects.clear();
	for( std::list<AIObject *>::iterator iter = m_passiveAIList.begin() ; iter != m_passiveAIList.end() ; ++iter )
	{
		delete (*iter);
	}
	m_passiveAIList.clear();
	m_activeAIList.clear();
	m_screenStartIter = m_levelObjects.begin();
	m_screenEndIter = m_levelObjects.end();
	m_xOffset = 0.0;
	return GameLoader::LoadLevel( m_levelFileName , this );
}

// Once upon a time this did something more than just the load method
// That was when men were men and a t-rex still scared the crap out of ya
// It cleared out all the existing level setup information, were load
// did not. It was found that Load would be best off using the code from
// Reload and reload was made no more. Think of reload now as the Red Headed
// Step child
/**
 * @todo: Refactor to remove calls to this method
 */
bool LevelObject::Reload()
{
	ScoreManager::Instance()->ResetLevel();
	return Load();
}

std::wstring LevelObject::GetTimerString()
{
	int seconds = m_timer / 1000;
	int minutes = seconds / 60;
	seconds = seconds % 60;
	return Converter::StringToWString( Converter::IntToString( minutes ) + ":" + ( seconds < 10 ? "0" : "" ) + Converter::IntToString( seconds ) );
}

void LevelObject::SetImageFolder( const std::wstring & imageFolder )
{
	m_imageFolder = imageFolder;
}

std::wstring LevelObject::GetImageFolder()
{
	return m_imageFolder;
}

void LevelObject::SetSpecialImages( int leftTextureId , int rightTextureId )
{
	m_specialTextureIds[0] = leftTextureId;
	m_specialTextureIds[1] = rightTextureId;
}

void LevelObject::FireSpecialPower( Square startingPos , bool direction )
{
	m_powerList.push_back( new PowerObject( startingPos , direction , m_specialTextureIds[0] , m_specialTextureIds[1] ) );
}