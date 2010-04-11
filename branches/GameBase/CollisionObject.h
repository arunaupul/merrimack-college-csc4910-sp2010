/**
 * @file CollisionObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * This file contains the interface used for the collision detection system
 *
 */
#ifndef _COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_

#include "GameEnums.h"

/**
 * @class CollisionObject
 * @brief Basic Collision Detection Object
 *
 * This class provides the proper interface needed to perfrom the
 * collision detection used throughout the game
 */
class CollisionObject
{
	/**
	 * Checks to see if object has collided with the current object
	 * @param object Object to check a collision against
	 * @return true if the object collided
	 */
	virtual bool CheckCollision( CollisionObject * object ) = 0;

	/**
	 * Handles the event of another object colliding with the current one
	 * @param side Side of the current object that has been hit
	 * @param damage Amount of damage to attempt to inflict upon the current object
	 * @return true if the current object wishes to return damage
	 */
	virtual bool Collide( CollisionSideEnum side , int damage ) = 0;
};

#endif /* _COLLISION_OBJECT_H_ */