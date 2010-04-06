#include "PowerUpBlock.h"

PowerUpBlock::PowerUpBlock( const Square & startingPos , PowerUpItem * item , unsigned int unusedTextureId , unsigned int usedTextureId )
:	GamePiece( startingPos , unusedTextureId ),
	m_blockUsed( false ),
	m_item( item )
{
	m_textureIds[0] = unusedTextureId;
	m_textureIds[1] = usedTextureId;
}

PowerUpBlock::~PowerUpBlock()
{
}

bool PowerUpBlock::Collide( CollisionSideEnum side , int damage )
{
	if( side == CS_BOTTOM && damage >= 1 )
	{
		m_blockUsed = true;
		m_textureId = m_textureIds[1];
		m_item->Activate();
	}
	return false;
}