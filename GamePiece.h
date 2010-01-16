#ifndef _GAME_PIECE_H_
#define _GAME_PIECE_H_

#include "Point.h"
#include "RgbaColor.h"

class GamePiece
{
public:
	GamePiece( double radius , Point center , RgbaColor color , bool moveNorth , int ownerNumber );
	~GamePiece();
	void Draw();
	bool ContainsPoint( Point point );
	void SetPoint( Point newPoint );
	bool CanMoveNorth();
	bool CanMoveSouth();
	int GetOwnerNumber();
	void KingPiece();
private:
	double m_radius;
	Point m_center;
	RgbaColor m_color;
	bool m_king;
	bool m_canMoveNorth;
	int m_ownerNumber;
};

#endif /* _GAME_PIECE_H_ */