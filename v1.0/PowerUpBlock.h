#ifndef _POWER_UP_BLOCK_H_
#define _POWER_UP_BLOCK_H_

#include "GamePiece.h"
#include "PowerUpItem.h"

class PowerUpBlock : public GamePiece {
public:
	PowerUpBlock( const Square & startingPos , PowerUpItem * item , unsigned int unusedTextureId , unsigned int usedTextureId );
	virtual ~PowerUpBlock();
	virtual bool Collide( CollisionSideEnum side , int damage );
private:
	unsigned int m_textureIds[2];
	bool m_blockUsed;
	PowerUpItem * m_item;
};

#endif /* _POWER_UP_BLOCK_H_ */