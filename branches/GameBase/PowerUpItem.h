/**
 * @file PowerUpItem.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Power up item, upon touching the game dude status is increased by 1
 *
 */
#ifndef _POWER_UP_ITEM_H_
#define _POWER_UP_ITEM_H_

#include "AIObject.h"
#include "AIType1.h"
#include "GameEnums.h"

/**
 * @class PowerUpItem
 * @brief Power Up Item
 *
 * Power up item, upon touching the game dude status is increased by 1
 */
class PowerUpItem :	public AIType1 {
public:
	/**
	 * Constructor
	 * @param startingPos Starting position of the object
	 * @param textureId Image to use
	 */
	PowerUpItem( const Square & startingPos , unsigned int textureId );

	/**
	 * Destructor
	 */
	virtual ~PowerUpItem();

	/**
	 * Checks if the object should be activated
	 * @param xOffset Not Used on this object
	 */
	virtual bool Trigger( double xOffset );

	/**
	 * Performs the update on the object
	 * @param ticks Number of ticks that have passed since the last update
	 */
	virtual void Update( int ticks );

	/**
	 * Set the object to return true on the new trigger
	 */
	void Activate();

	/**
	 * Set the vertical status
	 * @param status The new vertical status of the object
	 */
	void SetVerticalStatus( VerticalStatus status );
	
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
protected:
	/**
	 * Has the object been triggered
	 */
	bool m_triggered;

	/**
	 * How height has the object gone
	 */
	double m_jumpHeight;
};

#endif /* _POWER_UP_ITEM_H_ */