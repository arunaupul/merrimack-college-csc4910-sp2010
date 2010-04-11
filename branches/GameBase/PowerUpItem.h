/**
 * @file
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

class PowerUpItem :	public AIType1 {
public:
	PowerUpItem( const Square & startingPos , unsigned int textureId );
	virtual ~PowerUpItem();
	virtual bool Trigger( double xOffset );
	virtual void Update( int ticks );
	void Activate();
	void SetVerticalStatus( VerticalStatus status );
	virtual bool Collide( CollisionSideEnum side , int damage );
	virtual bool CheckCollision( CollisionObject * object );
protected:
	bool m_triggered;
	double m_jumpHeight;
};

#endif /* _POWER_UP_ITEM_H_ */