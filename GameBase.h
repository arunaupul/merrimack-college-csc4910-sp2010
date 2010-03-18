#ifndef _GAME_BASE_H_
#define _GAME_BASE_H_

#include <list>

#include "GlApplication.h"
#include "WorldObject.h"
#include "GameDude.h"

class GameBase : public GlApplication
{
public:
	GameBase();
	virtual ~GameBase();
	virtual bool PerformInit();
	virtual void KeyPressed( unsigned int key );
	virtual void KeyReleased( unsigned int key );
	virtual void PerformUpdate( int currentTick );
private:
	std::list<WorldObject *> m_worldList;
	std::list<WorldObject *>::iterator m_currentWorld;
	GameDude * m_gameDude;
};

#endif /* _GAME_BASE_H_ */