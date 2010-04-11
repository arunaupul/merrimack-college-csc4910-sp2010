/**
 * @file ScoreManager.h
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

/**
 * @class ScoreManager
 * @brief Tracks the players score
 *
 * Class to keep trace of the current playes score.
 * Singleton Object
 */
class ScoreManager {
public:
	/**
	 * Method to obtain the singleton instance
	 * @returns The singleton instance of the ScoreManager
	 */
	static ScoreManager * Instance();

	/**
	 * Get the current score
	 * @return The current score
	 */
	unsigned int GetCurrentScore();

	/**
	 * Add a given number of points to the player's score
	 * @param points Number of points to add to the player's score
	 * @param objectType Reason points are being added
	 */
	void AddToScore( unsigned int points , ScoreObject objectType );

	/**
	 * Reset the score and current level score to 0
	 */
	void Reset();

	/**
	 * Starts a new level. Resets the current level counter to 0
	 */
	void NewLevel();

	/**
	 * Removes points earned in this level from the score.
	 * Resets the current level count to 0.
	 */
	void ResetLevel();
protected:
	/**
	 * Constructor
	 */
	ScoreManager();

	/**
	 * Desctructor
	 */
	virtual ~ScoreManager();
	ScoreManager( const ScoreManager & );
	ScoreManager & operator=( const ScoreManager & );

	/**
	 * Total score so far
	 */
	unsigned int m_score;

	/**
	 * Score earned in the current level
	 */
	unsigned int m_levelScore;

	/**
	 * Singleton instance
	 */
	static ScoreManager * m_instance;
};

#endif /* _SCORE_MANAGER_H_ */