#pragma once
#include "GamePiece.h"

class LevelEndObject : public GamePiece
{
public:
	LevelEndObject( Square startingPos , unsigned int textureId );
	~LevelEndObject();
	virtual bool CheckCollision( CollisionObject * object );
	bool LevelDone();
private:
	bool m_levelDone;
};
