#include "WorldObject.h"
#include "GraphicLoaders.h"

#include <windows.h>
#include <gl\gl.h>

WorldObject::WorldObject( Point topLeft , Point bottomRight )
:	m_bottomRightPoint( bottomRight ),
	m_topLeftPoint( topLeft )
{
}

bool WorldObject::ObjectOnScreen( double leftBound , double rightBound )
{
	if( rightBound >= m_bottomRightPoint.x && leftBound <= m_topLeftPoint.x )
	{
		return true;
	}
	return false;
}

void WorldObject::Draw()
{
	glBindTexture( GL_TEXTURE_2D , GetTextureId() );
	glBegin( GL_POLYGON );
		glTexCoord2d( 0.0 , 0.0 );
		glVertex3d( m_topLeftPoint.x , m_topLeftPoint.y , m_topLeftPoint.z );
		glTexCoord2d( 0.0 , 1.0 );
		glVertex3d( m_topLeftPoint.x , m_bottomRightPoint.y , m_topLeftPoint.z );
		glTexCoord2d( 1.0 , 1.0 );
		glVertex3d( m_bottomRightPoint.x , m_bottomRightPoint.y , m_topLeftPoint.z );
		glTexCoord2d( 1.0 , 0.0 );
		glVertex3d( m_bottomRightPoint.x , m_topLeftPoint.y , m_topLeftPoint.z );
	glEnd();
}