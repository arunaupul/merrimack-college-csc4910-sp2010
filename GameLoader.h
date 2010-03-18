#ifndef _GAME_LOADER_H_
#define _GAME_LOADER_H_

#include <list>
#include <string>

#include "WorldObject.h"
#include "LevelObject.h"
#include "GameStructs.h"

namespace GameLoader {
	bool RunLoader( const std::wstring & worldsFileName , std::list<WorldObject *> & list , GameDude * dude );
	bool LoadLevel( const std::wstring & levelFileName , LevelObject * level );
	Square GameGridToCoords( double x , double y );
};

#endif /* _GAME_LOADER_H_ */