#ifndef _TEST_BLOCKS_H_
#define _TEST_BLOCKS_H_

#include "WorldObject.h"

class TestBlocks : public WorldObject
{
public:
	TestBlocks( double topLeftX , double topLeftY , double bottomRightX , double bottomRightY );
	~TestBlocks();
	unsigned int GetTextureId();
	void Draw();
	bool DetectCollision( GameDude * dude );
};

#endif /* _TEST_BLOCKS_H_ */