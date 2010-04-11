/**
 * @file AIType2.h
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

/**
 * @class AIType2
 * @brief Not so dumb AI Class
 *
 * Style 2 AI Controlled Enemy
 * AI will bounce of blocks and will not walk of cliffs
 */
class AIType2 :	public AIType1 {
public:
	/**
	 * Constructor
	 * @param startingPos Starting Position of the AI
	 * @param leftTextureId OpenGl TextureId for the image to display when the AI is moving left.
	 * @param rightTextureId OpenGl TextureId for the image to display when the AI is moving right.
	 */
	AIType2( const Square & startingPos , unsigned int leftTextureId , unsigned int rightTextureId );

	/**
	 * Destructor
	 */
	virtual ~AIType2();

	/**
	 * Performs the update on the AI Object
	 * Calls AIType1::Update after performing simple logic for Type 2
	 * @param ticks Number of ticks that have passed since the last update
	 */
	virtual void Update( int ticks );

	/**
	 * Checks to see if object has collided with the current object
	 * Calls AIType1::Collide. Keeps count of the number of collides per update
	 * @param object Object to check a collision against
	 * @return true if the object collided
	 */
	virtual bool Collide( CollisionSideEnum side , int damage );
protected:

	/**
	 * Traces the number of collides per update. Cleared to 0 with every call of update.
	 * If 1, the direction of the AI object will flip
	 */
	int m_verticalCollisionsThisPass;
};

#endif /* _AI_OBJECT_TYPE_2_H_ */
