#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_

#include "Point.h"
#include "RgbaColor.h"

class GamePiece
{
public:
	GamePiece( double radius , Point center , RgbaColor color );
	~GamePiece();
	void Draw();
	bool ContainsPoint( Point point );
	void SetPoint( Point newPoint );
private:
	double m_radius;
	Point m_center;
	RgbaColor m_color;
};

#endif /* _GAME_PIECE_H_ */