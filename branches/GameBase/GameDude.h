/**
 * @file GameDude.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Game Dude object represents the players avatar in the game
 * In maintians the states of the player
 *
 */
#ifndef _GAME_DUDE_H_
#define _GAME_DUDE_H_

#include "GamePiece.h"
#include "GameEnums.h"
#include "GameStructs.h"
#include "GlFrameworkObject.h"
#include "GraphicLoaders.h"

/**
 * @class GameDude
 * @brief The player avatar
 *
 * Game Dude object represents the players avatar in the game
 * In maintians the states of the player
 */
class GameDude : public GamePiece, public GlFrameworkObject {
public:
	/**
	 * Constructor
	 * @param startingPos Starting Location of the player
	 * @param smallTextureId Image Id of the small player
	 * @param largeTextureId Image Id of the large player
	 * @param specialTextureId Image Id of the special player
	 */
	GameDude( Square startingPos , unsigned int smallTextureId , unsigned int largeTextureId , unsigned int specialTextureId );

	/**
	 * Destructor
	 */
	virtual ~GameDude();

	/**
	 * Gets the current game dude status
	 * @returns The current GameDudeStatus
	 */
	GameDudeStatus GetDudeStatus();

	/**
	 * Gets the current horizontal status of the player
	 * @returns The current HoriztonalStatus
	 */
	HoriztonalStatus GetHorizontalStatus();

	/**
	 * Gets the current vertical status of the player
	 * @returns The current VerticalStatus
	 */
	VerticalStatus GetVerticalStatus();

	/**
	 * Move the player \a x units
	 * @param x Distance to move the player
	 * @return The new xOffset of the player
	 */
	double Move( double x );

	/**
	 * Performs the update on the player object
	 * @param ticks Number of ticks that have passed since the last update
	 */
	void Update( int ticks );

	/**
	 * Set the dude status
	 * @param newStatus The new GameDudeStatus
	 */
	void SetDudeStatus( GameDudeStatus newStatus );

	/**
	 * Set the Horizontal Status
	 * @param newStatus The new HorizontalStatus
	 */
	void SetHoriztonalStatus( HoriztonalStatus newStatus );

	/**
	 * Set the vertical status
	 * @param newStatus The new VerticalStatus
	 */
	void SetVerticalStatus( VerticalStatus newStatus );

	/**
	 * Handles the event of another object colliding with the current one
	 * @param side Side of the current object that has been hit
	 * @param damage Amount of damage to attempt to inflict upon the current object
	 * @return true if the current object wishes to return damage
	 */
	virtual bool Collide( CollisionSideEnum side , int damage );

	/**
	 * Draw the game dude
	 */
	virtual void Draw();

	/**
	 * Returns the current xOffset of the game dude
	 */
	void GetOffset();

	/**
	 * Moves the current position to have its left side start at newLeftX
	 * @param newLeftX The new left position
	 */
	void SetLeftBound( double newLeftX );

	/**
	 * Resets the dude to his starting position
	 * @param resetDudeStatus If the dude status should be reset
	 */
	void Reset( bool resetDudeStatus = true );

	/**
	 * Sets the crouching status of the GameDude
	 * @param status The new crouching status
	 */
	void SetCrouching( bool status );

	/**
	 * Gets the current facing of the GameDude
	 * @return 0 for left 1 for right
	 */
	bool GetFacing();

	/**
	 * Sets the new game dude images
	 * @param statusId Game dude image status to set
	 * @param textureId The new id to use
	 */
	void SetGameDudeImages( const GameDudeStatus statusId , GraphicLoaders::TextureIdentifier textureId );
private:
	/**
	 * Distance the game dude is from the start of the level
	 */
	double m_xOffset;

	/**
	 * The current height the player has jumped
	 */
	double m_jumpHeight;

	/**
	 * The current game dude status
	 */
	GameDudeStatus m_gameDudeStatus;

	/**
	 * The current horizontal status
	 */
	HoriztonalStatus m_hStatus;

	/**
	 * The current vertical status
	 */
	VerticalStatus m_vStatus;

	/**
	 * The game floor height, if the player falls below this,
	 * they are killed
	 */
	double m_gameFloor;

	/**
	 * The starting position of the player
	 */
	Square m_startingPos;

	/**
	 * Player images
	 */
	unsigned int m_textureIds[3];

	/**
	 * Crouching status
	 */
	bool m_crouching;

	/**
	 * Invinciblity timer
	 */
	int m_invincible;

	/**
	 * Last Direction the player was moving
	 */
	bool m_lastDirection;
};

#endif /* _GAME_DUDE_H_ */