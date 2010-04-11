/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Object used to check the level status.
 * This object will return true when the level is over
 *
 */
#ifndef _LEVEL_END_OBJECT_H_
#define _LEVEL_END_OBJECT_H_

#include "GamePiece.h"

class LevelEndObject : public GamePiece
{
public:
	LevelEndObject( Square startingPos , unsigned int textureId );
	~LevelEndObject();
	virtual bool CheckCollision( CollisionObject * object );
	bool LevelDone();
	virtual void Draw();
private:
	bool m_levelDone;
};

#endif /* _LEVEL_END_OBJECT_H_ */