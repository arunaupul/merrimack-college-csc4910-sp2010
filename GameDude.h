#ifndef _GAME_DUDE_H_
#define _GAME_DUDE_H_

#include "GlFrameworkobject.h"
#include "Point.h"
#include "GameDudeStatusEnum.h"
#include "GraphicLoaders.h"

class GameDude : public GlFrameworkObject
{
public:
	GameDude();
	~GameDude();
	void Draw();
	void Update( int ticks );
	void SetVerticalStatus( GameDudeVerticalStatus status );
	void SetHorizontalStatus( GameDudeHorizontalStatus status );
	GameDudeVerticalStatus GetVerticalStatus();
	GameDudeHorizontalStatus GetHorizontalStatus();
	Point GetCenterPoint();
	void SetCrouching( bool status );
	double GetXOffset();
	void Move( double x );
	Point GetTopLeftPoint();
	Point GetBottomRightPoint();
private:
	Point m_point;
	double m_jumpHeight;
	bool m_crouching;
	double m_xOffset;
	GameDudeHorizontalStatus m_hStatus;
	GameDudeVerticalStatus m_vStatus;
	GraphicLoaders::TextureIdentifier m_textureId;
};

#endif /* _GAME_DUDE_H_ */