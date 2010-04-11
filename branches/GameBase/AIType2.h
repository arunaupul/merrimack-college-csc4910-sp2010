/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Style 1 AI Controlled Enemy
 * AI will bounce of blocks and will not walk of cliffs
 *
 */
#ifndef _AI_OBJECT_TYPE_2_H_
#define _AI_OBJECT_TYPE_2_H_

#include "AIType1.h"
#include "GameEnums.h"

class AIType2 :	public AIType1 {
public:
	AIType2( const Square & startingPos , unsigned int leftTextureId , unsigned int rightTextureId );
	virtual ~AIType2();
	virtual void Update( int ticks );
	virtual bool Collide( CollisionSideEnum side , int damage );
protected:
	int m_verticalCollisionsThisPass;
};

#endif /* _AI_OBJECT_TYPE_2_H_ */
