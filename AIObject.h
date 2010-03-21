#ifndef _AI_OBJECT_H_
#define _AI_OBJECT_H_

#include "GamePiece.h"

class AIObject : public GamePiece {
public:
	AIObject( const Square & startingPos , unsigned int textureId );
	void SetVerticalStatus( VerticalStatus status );
	virtual bool Trigger( double xOffset ) = 0;
	virtual void Update( int ticks ) = 0;
protected:
	VerticalStatus m_vStatus;
	double m_gameFloor;
	bool m_active;
};

#endif /* _AI_OBJECT_H_ */