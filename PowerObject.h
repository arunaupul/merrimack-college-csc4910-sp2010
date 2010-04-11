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
	 */
	PowerObject( const Square & startingPos , bool direction , unsigned int leftTextureId , unsigned int rightTextureId );
	virtual ~PowerObject();
	virtual void Update( int ticks );
	virtual void Draw();
	bool IsDead();
	virtual bool CheckCollision( CollisionObject * object );
	virtual bool Collide( CollisionSideEnum side , int damage );
protected:
	bool m_direction;
	bool m_active;
};

#endif /* _POWER_OBJECT_H_ */