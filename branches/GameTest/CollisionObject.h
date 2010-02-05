#ifndef _COLLISION_OBJECT_H_
#define _COLLISION_OBJECT_H_

#include "GameDude.h"

class CollisionObject
{
	virtual bool DetectCollision( GameDude * dude ) = 0;
};

#endif /* _COLLISION_OBJECT_H_ */ 