/*
 *************************
 **   Ryan Fleming      **
 **   LifeGame          **
 **   Jan 27, 2010      **
 **         ,,,         **
 **        (0 0)        **
 **  ---ooO-(_)-Ooo---  **
 *************************
 * Version 1
 *
 * Main application class for the game of life 
 */

#ifndef _LIFE_GAME_H_
#define _LIFE_GAME_H_

#include "GlApplication.h"
#include "GamePiece.h"
#include "BoardSquare.h"

// 8 X 8 Board
#define NUM_BOARD_SQUARES	2460
#define NUM_ROWS			41
#define NUM_COLUMNS			60


class LifeGame : public GlApplication
{
public:
	LifeGame();										// Constructor
	~LifeGame();									// Destructor
protected:
	void PerformUpdate( int currentTick );			// Override the default perform update
	bool PerformInit();								// Perform custom init code
	void LeftMouseClick( Point & clickedPoint );	// Override the default left mouse click handler
	void RightMouseClick( Point & clickedPoint );	// Override the default right mouse click handler
	void KeyPressed( unsigned int key );			// Override the default keypress handler
private:
	bool m_runningSim;								// Is the simulation running
	BoardSquare * m_board[NUM_ROWS][NUM_COLUMNS];	// Board
	int m_ticksPassed;
};

#endif /* _LIFE_GAME_H_ */