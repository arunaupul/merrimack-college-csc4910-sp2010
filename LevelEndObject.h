/**
 * @file LevelEndObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Object used to check the level status.
 * This object will return true when the level is over
 *
 */
#ifndef _LEVEL_END_OBJECT_H_
#define _LEVEL_END_OBJECT_H_

#include "GamePiece.h"

/**
 * @class LevelEndObject
 * @brief Object used to track if a level has ended
 *
 * Object used to check the level status.
 * This object will return true when the level is over
 */
class LevelEndObject : public GamePiece {
public:
	/**
	 * Constructor
	 * @param startingPos Position of the levelEndObject
	 * @param textureId Image to use for the object
	 */
	LevelEndObject( Square startingPos , unsigned int textureId );

	/**
	 * Destructor
	 */
	~LevelEndObject();

	/**
	 * Checks to see if object has collided with the current object
	 * @param object Object to check a collision against
	 * @return true if the object collided
	 */
	virtual bool CheckCollision( CollisionObject * object );

	/**
	 * Check if a level has been completed
	 * @return True if the level has ended
	 */
	bool LevelDone();

	/**
	 * Draw the object
	 */
	virtual void Draw();
private:
	/**
	 * Status if the level has ended
	 */
	bool m_levelDone;
};

#endif /* _LEVEL_END_OBJECT_H_ */