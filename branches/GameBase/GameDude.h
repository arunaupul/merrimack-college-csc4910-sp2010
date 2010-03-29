#ifndef _GAME_DUDE_H_
#define _GAME_DUDE_H_

#include "GamePiece.h"
#include "GameEnums.h"
#include "GameStructs.h"
#include "GlFrameworkObject.h"

class GameDude : public GamePiece, public GlFrameworkObject {
public:
	GameDude( Square startingPos , unsigned int smallTextureId , unsigned int largeTextureId , unsigned int specialTextureId );
	virtual ~GameDude();
	GameDudeStatus GetDudeStatus();
	HoriztonalStatus GetHorizontalStatus();
	VerticalStatus GetVerticalStatus();
	double Move( double x );
	void Update( int ticks );
	void SetDudeStatus( GameDudeStatus newStatus );
	void SetHoriztonalStatus( HoriztonalStatus newStatus );
	void SetVerticalStatus( VerticalStatus newStatus );
	virtual bool Collide( CollisionSideEnum side , int damage );
	virtual void Draw();
	void GetOffset();
	void SetLeftBound( double newLeftX );
	void Reset( bool resetDudeStatus = true );
	void SetCrouching( bool status );
private:
	double m_xOffset;
	double m_jumpHeight;
	GameDudeStatus m_gameDudeStatus;
	HoriztonalStatus m_hStatus;
	VerticalStatus m_vStatus;
	double m_gameFloor;
	Square m_startingPos;
	unsigned int m_textureIds[3];
	bool m_crouching;
};

#endif /* _GAME_DUDE_H_ */