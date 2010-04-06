#include "AIObject.h"

#include <windows.h>
#include <gl\gl.h>

AIObject::AIObject( const Square & startingPos , unsigned int textureId )
:	GamePiece( startingPos , textureId ),
 	m_active( false ),
	m_vStatus( VS_NONE ),
	m_gameFloor( -8.0 ),
	m_killed( false )
{
}

void AIObject::SetVerticalStatus( VerticalStatus status )
{
	m_vStatus = status;
}

void AIObject::Draw()
{
	if( m_active && !m_killed )
	{
		glEnable( GL_BLEND );
		glDisable( GL_DEPTH_TEST );
		GamePiece::Draw();
		glDisable( GL_BLEND );
		glEnable( GL_DEPTH_TEST );
	}
}

bool AIObject::GetActiveStatus()
{
	return m_active && !m_killed;
}