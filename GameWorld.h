#ifndef _GAME_WORLD_H_
#define _GAME_WORLD_H_

#include "GlFrameworkObject.h"
#include "WorldObject.h"
#include "BackGroundManager.h"
#include "GameDude.h"
#include <list>

class GameWorld : public GlFrameworkObject
{
public:
	GameWorld( GameDude * gameDude );
	~GameWorld();
	void Draw();
	void Update( int ticks );
	void Move( double x );
private:
	std::list< WorldObject * > m_worldObjectList;
	BackGroundManager * m_background;
	GameDude * m_gameDude;
	double m_currentOffset;
	double m_screenWidth;
	double m_worldLength;
	double m_offScreenDrawDistance;
	std::list< WorldObject * >::iterator m_startIter;
	std::list< WorldObject * >::iterator m_stopIter;
};

#endif /* _GAME_WORLD_H_ */