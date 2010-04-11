/**
 * @file PowerUpBlock.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Special Power Block. Upon hitting, it triggers the PowerUpItem
 *
 */
#ifndef _POWER_UP_BLOCK_H_
#define _POWER_UP_BLOCK_H_

#include "GamePiece.h"
#include "PowerUpItem.h"

/**
 * @class PowerUpBlock
 * @brief Block that creates a PowerUpItem
 *
 * Special Power Block. Upon hitting, it triggers the PowerUpItem
 */
class PowerUpBlock : public GamePiece {
public:
	/**
	 * Constructor
	 * @param startingPos The position of the block
	 * @param item PowerUpItem to trigger once the block is hit
	 * @param unusedTextureId Image to display before the block is hit
	 * @param usedTextureId Image to display after the block is hit
	 */
	PowerUpBlock( const Square & startingPos , PowerUpItem * item , unsigned int unusedTextureId , unsigned int usedTextureId );

	/**
	 * Destructor
	 */
	virtual ~PowerUpBlock();

	/**
	 * Handles the event of another object colliding with the current one
	 * @param side Side of the current object that has been hit
	 * @param damage Amount of damage to attempt to inflict upon the current object
	 * @return true if the current object wishes to return damage
	 */
	virtual bool Collide( CollisionSideEnum side , int damage );
private:
	/**
	 * Texture Ids to use for the power up block
	 */
	unsigned int m_textureIds[2];

	/**
	 * Has the power block been hit
	 */
	bool m_blockUsed;

	/**
	 * Item to trigger when hit
	 */
	PowerUpItem * m_item;
};

#endif /* _POWER_UP_BLOCK_H_ */