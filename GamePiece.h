/**
 * @file GamePiece.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Base class for all objects the player can see on the screen
 * and the GameDude can interact with.
 *
 */
#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_

#include "GameStructs.h"
#include "CollisionObject.h"

/**
 * @class GamePiece
 * @brief General Game Object
 *
 * Base class for all objects the player can see on the screen
 * and the GameDude can interact with.
 */
class GamePiece : public CollisionObject {
public:
	/**
	 * Constructor
	 * @param startingPos Location of the GamePiece
	 * @param textureId Id of the texture of the GamePiece
	 */
	GamePiece( const Square & startingPos , unsigned int textureId );

	/**
	 * Draws the GamePiece
	 */
	virtual void Draw();

	/**
	 * Obtains the current location of the GamePiece
	 */
	Square GetCurrentPosition();
	
	/**
	 * Handles the event of another object colliding with the current one
	 * @param side Side of the current object that has been hit
	 * @param damage Amount of damage to attempt to inflict upon the current object
	 * @return true if the current object wishes to return damage
	 */
	virtual bool Collide( CollisionSideEnum side , int damage );
	
	/**
	 * Checks to see if object has collided with the current object
	 * @param object Object to check a collision against
	 * @return true if the object collided
	 */
	virtual bool CheckCollision( CollisionObject * object );

	/**
	 * Method to check if the object is on the screen
	 * @param leftX Left side of the screen
	 * @param rightX Right side of the screen
	 * @return True is the object is on the screen
	 */
	virtual bool OnScreen( double leftX , double rightX );

	/**
	 * Sets the current position to the newPos
	 * @param newPos The objects new position
	 */
	void SetPosition( const Square & newPos );
protected:
	/**
	 * The position and size of the object
	 */
	Square m_currentLocation;

	/**
	 * Texture id to draw with the object
	 */
	unsigned int m_textureId;

	/**
	 * Has the block been broken
	 */
	bool m_broken;
};

#endif /* _GAME_PIECE_H_ */