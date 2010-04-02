#include "ScoreManager.h"

ScoreManager::ScoreManager()
:	m_score( 0 )
{
}

ScoreManager::~ScoreManager()
{
}

void ScoreManager::AddToScore( unsigned int points , ScoreObject objectType )
{
	m_score += points;
	m_levelScore += points;
}

unsigned int ScoreManager::GetCurrentScore()
{
	return m_score;
}

void ScoreManager::Reset()
{
	m_levelScore = 0;
	m_score = 0;
}

void ScoreManager::ResetLevel()
{
	m_score -= m_levelScore;
	m_levelScore = 0;
}

void ScoreManager::NewLevel()
{
	m_levelScore = 0;
}

ScoreManager * ScoreManager::Instance()
{
	if( m_instance == 0 )
	{
		m_instance = new ScoreManager();
	}
	return m_instance;
}

// Stub
ScoreManager::ScoreManager( const ScoreManager & temp )
{
}

// Stub
ScoreManager & ScoreManager::operator=( const ScoreManager & temp )
{
	return *((ScoreManager *)0);
}

ScoreManager * ScoreManager::m_instance = 0;