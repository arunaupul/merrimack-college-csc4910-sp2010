/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Class to keep trace of the current playes score.
 * Singleton Object
 *
 */
#ifndef _SCORE_MANAGER_H_
#define _SCORE_MANAGER_H_

#include "GameEnums.h"

class ScoreManager {
public:
	static ScoreManager * Instance();
	unsigned int GetCurrentScore();
	void AddToScore( unsigned int points , ScoreObject objectType );
	void Reset();
	void NewLevel();
	void ResetLevel();
protected:
	ScoreManager();
	virtual ~ScoreManager();
	ScoreManager( const ScoreManager & );
	ScoreManager & operator=( const ScoreManager & );
	unsigned int m_score;
	unsigned int m_levelScore;
	static ScoreManager * m_instance;
};

#endif /* _SCORE_MANAGER_H_ */