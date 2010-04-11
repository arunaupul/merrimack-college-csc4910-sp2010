/**
 * @file AIObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * File contains the base class for all AI controlled objects
 *
 */
#ifndef _AI_OBJECT_H_
#define _AI_OBJECT_H_

#include "GamePiece.h"

/**
 * @class AIObject
 * @brief Base class for all AI controled objects.
 *
 * Base class for all AI controled objects
 */
class AIObject : public GamePiece {
public:
	/**
	 * Constructor
	 * @param startingPos Starting location of the AI object
	 * @param textureId Image to display for the object
	 */
	AIObject( const Square & startingPos , unsigned int textureId );

	/**
	 * Sets the current Vertical Status of the AI object
	 * @param status New vertical status for the AIObject
	 */
	virtual void SetVerticalStatus( VerticalStatus status );

	/**
	 * Checks to see if the AI Object is within range of the game dude.
	 * @param xOffset The current x offset of the game dude from the level start
	 * @return True if AI Object should be triggered
	 */
	virtual bool Trigger( double xOffset ) = 0;

	/**
	 * Performs the update on the AI Object
	 * @param ticks Number of ticks that have passed since the last update
	 */
	virtual void Update( int ticks ) = 0;

	/**
	 * General Draw Method for the AI Object
	 */
	virtual void Draw();

	/**
	 * Method to check if the AI Object is currently active in the game
	 * @return True if the object is active
	 */
	virtual bool GetActiveStatus();
protected:
	/**
	 * The current vertical status of the AI Object
	 */
	VerticalStatus m_vStatus;

	/**
	 * The game floor. If the Y of the AI object drops below this, it should go inactive
	 */
	double m_gameFloor;

	/**
	 * If the current AI has been activated
	 */
	bool m_active;

	/**
	 * If the AI has been killed
	 */
	bool m_killed;
};

#endif /* _AI_OBJECT_H_ */