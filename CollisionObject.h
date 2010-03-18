#ifndef _COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_

#include "GameEnums.h"

class CollisionObject
{
	virtual bool CheckCollision( CollisionObject * object ) = 0;
	virtual bool Collide( CollisionSideEnum side , int damage ) = 0;
};

#endif /* _COLLISION_OBJECT_H_ */