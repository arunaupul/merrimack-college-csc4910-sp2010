#ifndef _BOARD_SQUARE_H_
#define _BOARD_SQUARE_H_

#include "Point.h"
#include "RgbaColor.h"
#include "GamePiece.h"
#include "GlFrameworkObject.h"

class BoardSquare : public GlFrameworkObject
{
public:
	BoardSquare( Point point , int row , int column );
	~BoardSquare();

	void Draw();

	void Update( int ticks );

	// Get/Set the game piece
	void SetGamePiece( GamePiece * piece );
	GamePiece * GetGamePiece();

	bool ContainsPoint( Point point );

	int GetColumn();
	int GetRow();

	bool GetCurrentStatus();
	void SetCurrentStatus( bool status );
	void SetNextStatus( bool status );
	void SetNextAsCurrent();

private:
	Point m_point;
	GamePiece * m_gamePiece;

	int m_row;
	int m_column;

	bool m_currentStatus;
	bool m_nextStatus;
};

#endif /* _BOARD_SQUARE_H_ */