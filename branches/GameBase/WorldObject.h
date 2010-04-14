/**
 * @file WorldObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Represents a current world within the game. Handles level loading and management
 *
 */
#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include <list>
#include <string>

#include "GlFrameworkObject.h"
#include "LevelObject.h"
#include "GameDude.h"

/**
 * @class WorldObject
 * @brief World in the game
 *
 * Represents a current world within the game. Handles level loading and management
 */
class WorldObject : public GlFrameworkObject {
public:
	/**
	 * Constructor
	 * @param name World Name
	 * @param dude The player's GameDude
	 */
	WorldObject( const std::wstring & name , GameDude * dude );

	/**
	 * Sets the world's world name
	 * @param name The new name for the world
	 */
	void SetWorldName( const std::wstring & name );

	/**
	 * Destructor
	 */
	virtual ~WorldObject();

	/**
	 * Draw the world
	 */
	void Draw();

	/**
	 * Method to update the object 
	 * @param ticks Number of ticks passed since the last call to update
	 */
	void Update( int ticks );

	/**
	 * Starts the current world
	 */
	void Start();

	/**
	 * Move the player \a distance through the world
	 * @param distance Distance to move
	 * @return New xOffset
	 */
	double Move( double distance );

	/**
	 * Adds a level to the current world
	 * @remarks Should only be used by the GameLoaders
	 * @param level Level to add
	 */
	void AddLevel( LevelObject * level );

	/**
	 * Checks to see if the world is done
	 * @return true if the world has been completed
	 */
	bool WorldDone();

	/**
	 * Restarts the current level in a world
	 * @return true if successful
	 */
	bool RestartCurrentLevel();

	/**
	 * Get time remain string
	 * @return Time remaining as a string
	 */
	std::wstring GetTimerString();

	/**
	 * Fire the special power of the game dude
	 * @param startingPos Starting Position of the fire
	 * @param direction Direction to fire
	 */
	void FireSpecialPower( Square startingPos , bool direction );

	/**
	 * Gets the current loading status
	 * @return True if the current level is loading
	 */
	bool IsLoading();

	/**
	 * Gets the world-level string
	 * @return Level String
	 */
	std::wstring GetNameString();

protected:
	/**
	 * The world's name
	 */
	std::wstring m_worldName;

	/**
	 * List of levels in the world
	 */
	std::list<LevelObject *> m_levelList;

	/**
	 * The current level for the world
	 */
	std::list<LevelObject *>::iterator m_currentLevel;

	/**
	 * The current game dude
	 */
	GameDude * m_gameDude;

	/**
	 * Indicates that on the next update, the new level will load
	 */
	bool m_loadingLevel;

	/**
	 * Image to use as a loading screen
	 */
	unsigned int m_loadingScreenTextureId;

	/**
	 * Image to use as a reloading screen
	 */
	unsigned int m_reloadingScreenTextureId;

	/**
	 * Track if this is the first load
	 */
	bool m_firstLoad;

	/**
	 * Track if the world is reloading a level
	 */
	bool m_reloading;

};

#endif /* _WORLD_OBJECT_H_ */