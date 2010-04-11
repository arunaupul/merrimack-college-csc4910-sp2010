/**
 * @file PowerObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * The object that game dude fires when using the special powers
 *
 */

#ifndef _POWER_OBJECT_H_
#define _POWER_OBJECT_H_

#include "GamePiece.h"
#include "GameStructs.h"

/**
 * @class PowerObject
 * @brief The special power
 *
 * The object that game dude fires when using the special powers
 */
class PowerObject : public GamePiece {
public:
	/**
	 * Constuctor
	 * @param startingPos Starting position of the special power
	 * @param direction Direction the object should be moving
	 * @param leftTextureId Left moving image
	 * @param rightTextureId Right moving image
	 */
	PowerObject( const Square & startingPos , bool direction , unsigned int leftTextureId , unsigned int rightTextureId );

	/**
	 * Destructor
	 */
	virtual ~PowerObject();

	/**
	 * Updates the power object
	 * @param ticks Ticks passed since the last call to update
	 */
	virtual void Update( int ticks );

	/**
	 * Draw the PowerObject
	 */
	virtual void Draw();

	/**
	 * Check if the PowerObject has died
	 * @return If the power object has hit something
	 */
	bool IsDead();
	
	/**
	 * Checks to see if object has collided with the current object
	 * @param object Object to check a collision against
	 * @return true if the object collided
	 */
	virtual bool CheckCollision( CollisionObject * object );
	
	/**
	 * Handles the event of another object colliding with the current one
	 * @param side Side of the current object that has been hit
	 * @param damage Amount of damage to attempt to inflict upon the current object
	 * @return true if the current object wishes to return damage
	 */
	virtual bool Collide( CollisionSideEnum side , int damage );
protected:
	/**
	 * Direction the object is moving
	 */
	bool m_direction;

	/**
	 * Is the piece currently active
	 */
	bool m_active;
};

#endif /* _POWER_OBJECT_H_ */