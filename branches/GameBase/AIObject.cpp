#include "AIObject.h"

AIObject::AIObject( const Square & startingPos , unsigned int textureId )
:	GamePiece( startingPos , textureId ),
 	m_active( false ),
	m_vStatus( VS_NONE ),
	m_gameFloor( 0.0 )
{
}

void AIObject::SetVerticalStatus( VerticalStatus status )
{
	m_vStatus = status;
}