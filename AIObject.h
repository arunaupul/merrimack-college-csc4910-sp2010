#ifndef _AI_OBJECT_H_
#define _AI_OBJECT_H_

#include "GamePiece.h"

class AIObject : public GamePiece {
public:
	AIObject();
	virtual bool Triiger( double xOffset ) = 0;
	virtual void Update( int ticks ) = 0;
};

#endif /* _AI_OBJECT_H_ */