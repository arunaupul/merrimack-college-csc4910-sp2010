#ifndef _AI_TYPE_1_H_
#define _AI_TYPE_1_H_

#include "AIObject.h"
#include "GameEnums.h"

class AIType1 :	public AIObject {
public:
	AIType1( const Square & startingPos , unsigned int textureId );
	virtual ~AIType1();
	virtual void Update( int ticks );
	virtual bool Trigger( double xOffset );
	virtual bool Collide( CollisionSideEnum side , int damage );
private:
	bool m_direction;
};

#endif /* _AI_TYPE_1_H_ */