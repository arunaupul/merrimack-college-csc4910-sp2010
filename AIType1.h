/**
 * @file AIType1.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Style 1 AI Controlled Enemy
 * AI will bounce of blocks and walk of cliffs
 *
 */
#ifndef _AI_TYPE_1_H_
#define _AI_TYPE_1_H_

#include "AIObject.h"
#include "GameEnums.h"

/**
 * @class AIType1
 * @brief Dumb AI Class

 * Style 1 AI Controlled Enemy
 * AI will bounce of blocks and walk of cliffs
 */
class AIType1 :	public AIObject {
public:
	/**
	 * Constructor
	 * @param startingPos Starting Position of the AI
	 * @param leftTextureId OpenGl TextureId for the image to display when the AI is moving left.
	 * @param rightTextureId OpenGl TextureId for the image to display when the AI is moving right.
	 */
	AIType1( const Square & startingPos , unsigned int leftTextureId , unsigned int rightTextureId );

	/**
	 * Destructor
	 */
	virtual ~AIType1();

	/**
	 * Performs the update on the AI Object
	 * @param ticks Number of ticks that have passed since the last update
	 */
	virtual void Update( int ticks );
	
	/**
	 * Checks to see if the AI Object is within range of the game dude.
	 * @param xOffset The current x offset of the game dude from the level start
	 * @return True if AI Object should be triggered
	 */
	virtual bool Trigger( double xOffset );
	
	/**
	 * Checks to see if object has collided with the current object
	 * @param object Object to check a collision against
	 * @return true if the object collided
	 */
	virtual bool Collide( CollisionSideEnum side , int damage );
	
	/**
	 * Handles the event of another object colliding with the current one
	 * @param side Side of the current object that has been hit
	 * @param damage Amount of damage to attempt to inflict upon the current object
	 * @return true if the current object wishes to return damage
	 */
	virtual bool CheckCollision( CollisionObject * object );
protected:
	/**
	 * Monitors the moving direction of the AI Object
	 */
	bool m_direction;

	/**
	 * List of texture ids used during the operation of the object
	 */
	unsigned int m_textureIds[2];

	/**
	 * Method used to switch the moving direction of the AIObject
	 * This method handles the textureIds and other status updates
	 */
	void SwitchDirections( bool direction );
};

#endif /* _AI_TYPE_1_H_ */