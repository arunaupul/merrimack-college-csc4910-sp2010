#ifndef _GAME_DUDE_H_
#define _GAME_DUDE_H_

#include "GamePiece.h"
#include "GameEnums.h"
#include "GameStructs.h"
#include "GlFrameworkObject.h"

class GameDude : public GamePiece, public GlFrameworkObject {
public:
	GameDude( Square startingPos , unsigned int textureId );
	virtual ~GameDude();
	GameDudeStatus GetDudeStatus();
	HoriztonalStatus GetHorizontalStatus();
	VerticalStatus GetVerticalstatus();
	double Move( double x );
	void Update( int ticks );
	void SetDudeStatus( GameDudeStatus newStatus );
	void SetHoriztonalStatus( HoriztonalStatus newStatus );
	void SetVerticalStatus( VerticalStatus newStatus );
	virtual bool Collide( CollisionSideEnum side , int damage );
	virtual void Draw();
	void GetOffset();
	void SetLeftBound( double newLeftX );
private:
	double m_xOffset;
	double m_jumpHeight;
	GameDudeStatus m_gameDudeStatus;
	HoriztonalStatus m_hStatus;
	VerticalStatus m_vStatus;
	double m_gameFloor;
};

#endif /* _GAME_DUDE_H_ */