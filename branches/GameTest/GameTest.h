#ifndef _GAME_TEST_H_
#define _GAME_TEST_H_

#include "GlApplication.h"
#include "GameDude.h"
#include "GameWorld.h"

class GameTest : public GlApplication
{
public:
	GameTest();
	~GameTest();
	void KeyPressed( unsigned int key );
	void PerformUpdate( int currentTick );
	void KeyReleased( unsigned int key );
	bool PerformInit();
private:
	GameDude * m_dude;
	GameWorld * m_gameWorld;
};

#endif /* _GAME_TEST_H_ */