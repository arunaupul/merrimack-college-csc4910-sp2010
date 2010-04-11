/**
 * @file GameLoader.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * This namespace supplies the neccessary functions to load
 * All game control objects from the given files
 *
 */
#ifndef _GAME_LOADER_H_
#define _GAME_LOADER_H_

#include <list>
#include <string>

#include "WorldObject.h"
#include "LevelObject.h"
#include "GameStructs.h"

/**
 * @namespace GameLoader
 * @brief Used to convert images into openGL texture ids
 *
 * This namespace supplies the neccessary functions to load
 * All game control objects from the given files
 */
namespace GameLoader {
	/**
	 * Loads the world list with WorldObjects from the worldsFileName
	 * @param worldsFileName File Path to a worlds file
	 * @param list World List to load
	 * @param dude GameDude to hand to each world
	 * @return True on success
	 */
	bool RunLoader( const std::wstring & worldsFileName , std::list<WorldObject *> & list , GameDude * dude );

	/**
	 * Loads a given level from a file
	 * @param levelFileName Level File to load
	 * @param level LevelObject to load
	 * @return True on success
	 */
	bool LoadLevel( const std::wstring & levelFileName , LevelObject * level );

	/**
	 * Method to convert from the game grid to openGL coords
	 * @param x X coord of the grid
	 * @param y Y corrd of the grid
	 * @return Square representing the openGL coords of the grid
	 */
	Square GameGridToCoords( double x , double y );
};

#endif /* _GAME_LOADER_H_ */