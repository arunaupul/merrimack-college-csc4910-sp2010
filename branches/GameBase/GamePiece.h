/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Base class for all objects the player can see on the screen
 * and the GameDude can interact with.
 *
 */
#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_

#include "GameStructs.h"
#include "CollisionObject.h"

class GamePiece : public CollisionObject {
public:
	GamePiece( const Square & startingPos , unsigned int textureId );
	virtual void Draw();
	Square GetCurrentPosition();
	virtual bool Collide( CollisionSideEnum side , int damage );
	virtual bool CheckCollision( CollisionObject * object );
	virtual bool OnScreen( double leftX , double rightX );
	void SetLeftBound( double newLeftX );
	void SetPosition( const Square & newPos );
protected:
	Square m_currentLocation;
	unsigned int m_textureId;
	bool m_broken;
};

#endif /* _GAME_PIECE_H_ */