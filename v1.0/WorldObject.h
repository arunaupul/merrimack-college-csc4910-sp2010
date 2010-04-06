#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include <list>
#include <string>

#include "GlFrameworkObject.h"
#include "LevelObject.h"
#include "GameDude.h"

class WorldObject : public GlFrameworkObject {
public:
	WorldObject( const std::wstring & name , GameDude * dude );
	void SetWorldName( const std::wstring & name );
	virtual ~WorldObject();
	void Draw();
	void Update( int ticks );
	void Start();
	double Move( double distance );
	void AddLevel( LevelObject * level );
	bool WorldDone();
	bool RestartCurrentLevel();
	std::wstring GetTimerString();
	void FireSpecialPower( Square startingPos , bool direction );
protected:
	std::wstring m_worldName;
	std::list<LevelObject *> m_levelList;
	std::list<LevelObject *>::iterator m_currentLevel;
	GameDude * m_gameDude;

};

#endif /* _WORLD_OBJECT_H_ */