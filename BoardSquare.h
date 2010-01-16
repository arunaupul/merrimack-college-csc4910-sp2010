#ifndef _BOARD_SQUARE_H_
#define _BOARD_SQUARE_H_

#include "Point.h"
#include "RgbaColor.h"
#include "GamePiece.h"

class BoardSquare
{
public:
	BoardSquare( Point point , bool isRed , int row , int column );
	~BoardSquare();

	void Draw();

	// Get/Set the game piece
	void SetGamePiece( GamePiece * piece );
	GamePiece * GetGamePiece();

	bool ContainsPoint( Point point );

	bool IsValidMove();

	int GetColumn();
	int GetRow();

private:
	RgbaColor m_color;
	Point m_point;
	GamePiece * m_gamePiece;

	int m_row;
	int m_column;

	bool m_validMove;
};

#endif /* _BOARD_SQUARE_H_ */