/**
 * @file LevelObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Represents a level within the game. Handles all AI objects,
 * Special Powers and block collisions
 *
 */
#ifndef _LEVEL_OBJECT_H_
#define _LEVEL_OBJECT_H_

#include <string>
#include <list>

#include "AIObject.h"
#include "GamePiece.h"
#include "BackGroundManager.h"
#include "GameDude.h"
#include "LevelEndObject.h"
#include "PowerObject.h"

/**
 * @class LevelObject
 * @brief Level in the game
 *
 * Represents a level within the game. Handles all AI objects,
 * Special Powers and block collisions
 */
class LevelObject {
public:
	/**
	 * Constructor
	 * @param levelName The level's name
	 */
	LevelObject( const std::wstring & levelName );

	/**
	 * Destructor
	 */
	virtual ~LevelObject();

	/**
	 * Draw the level
	 */
	void Draw();

	/**
	 * Update the current level
	 * @param ticks Number of ticks since the last update
	 * @param gameDude GameDude object to collide against
	 */
	bool Update( int ticks , GameDude * gameDude );

	/**
	 * Move the level \a distance
	 * @param distance Distance to move
	 * @return The new xOffset
	 */
	double Move( double distance );

	/**
	 * Adds a general GamePiece to the level
	 * @param piece GamePiece to add to the level
	 */
	void AddGamePiece( GamePiece * piece );

	/**
	 * Adds a general AIObject to the level
	 * @param object AIObject to add to the level
	 */
	void AddAIObject( AIObject * object );

	/**
	 * Starts the level
	 */
	void Start();

	/**
	 * Set the level end object for a level
	 * @param object Object to use as the level end indicator
	 */
	void SetLevelEndObject( LevelEndObject * object );

	/**
	 * Sets the level file name. This file will be used to load the level.
	 * @param levelFileName Level file to load
	 */
	void SetLevelFileName( const std::wstring & levelFileName );

	/**
	 * Sets the image folder for the level. Textures will be loaded from this folder.
	 * @param imageFolder Folder name where the images are located
	 */
	void SetImageFolder( const std::wstring & imageFolder );

	/**
	 * Get the Image Folder
	 * @return The folder name where the images are located
	 */
	std::wstring GetImageFolder();

	/**
	 * Loads the level from the fileName
	 */
	bool Load();

	/**
	 * Unloads the level
	 */
	void UnLoad();

	/**
	 * Reloads the level from the begining
	 */
	bool Reload();

	/**
	 * Get time remain string
	 * @return Time remaining as a string
	 */
	std::wstring GetTimerString();

	/**
	 * Fires a special power object
	 * @param startingPos Starting location of the PowerObject
	 * @param direction Direction of the PowerObject
	 */
	void FireSpecialPower( Square startingPos , bool direction );

	/**
	 * Sets the images to use for the PowerObject
	 * @param leftTextureId Image of a left moving PowerObject
	 * @param rightTextureId Image of a right moving PowerObject
	 */
	void SetSpecialImages( int leftTextureId , int rightTextureId );

	/**
	 * Gets the level name
	 * @return Level name
	 */
	std::wstring GetLevelName();
protected:
	/**
	 * All objects in the level
	 */
	std::list<GamePiece *> m_levelObjects;

	/**
	 * List off none activated AI Objects
	 */
	std::list<AIObject *> m_passiveAIList;

	/**
	 * Name of the level
	 */
	std::wstring m_levelName;

	/**
	 * Distance the player has moved from the begining of the level
	 */
	double m_xOffset;

	/**
	 * The maximum distance a player can move into the level
	 */
	double m_maxXOffset;

	/**
	 * The background image for the level
	 */
	BackGroundManager * m_backGroundManager;

	/**
	 * The screen width in openGL units
	 */
	double m_screenWidth;
private:
	/**
	 * List of currently active AI Objects
	 */
	std::list<AIObject *> m_activeAIList;

	/**
	 * Marks the right side of the screen
	 */
	std::list<GamePiece *>::iterator m_screenEndIter;

	/**
	 * Marks the left side of the screen
	 */
	std::list<GamePiece *>::iterator m_screenStartIter;

	/**
	 * List of power objects shot by the player
	 */
	std::list<PowerObject *> m_powerList;

	/**
	 * Object to control the level end
	 */
	LevelEndObject * m_levelEndObject;

	/**
	 * Level load file name
	 */
	std::wstring m_levelFileName;

	/**
	 * Level image file folder path
	 */
	std::wstring m_imageFolder;

	/**
	 * The current timer for the level
	 */
	int m_timer;

	/**
	 * The images used for the special powers
	 */
	int m_specialTextureIds[2];

	GraphicLoaders::TextureIdentifier * m_textureList;
};

#endif /* _LEVL_OBJECT_H_ */