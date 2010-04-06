/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Base class for all AI controled objects
 *
 */
#ifndef _AI_OBJECT_H_
#define _AI_OBJECT_H_

#include "GamePiece.h"

/**
 * @class AIObject
 * Base class for all AI controled objects
 */
class AIObject : public GamePiece {
public:
	AIObject( const Square & startingPos , unsigned int textureId );
	virtual void SetVerticalStatus( VerticalStatus status );
	virtual bool Trigger( double xOffset ) = 0;
	virtual void Update( int ticks ) = 0;
	virtual void Draw();
	virtual bool GetActiveStatus();
protected:
	VerticalStatus m_vStatus;
	double m_gameFloor;
	bool m_active;
	bool m_killed;
};

#endif /* _AI_OBJECT_H_ */