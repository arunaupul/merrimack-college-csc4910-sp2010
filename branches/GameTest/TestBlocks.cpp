#include "TestBlocks.h"

#include <windows.h>
#include <gl\gl.h>

TestBlocks::TestBlocks( double topLeftX , double topLeftY , double bottomRightX , double bottomRightY )
:	WorldObject( Point( topLeftX , topLeftY , 0.0 ) , Point( bottomRightX , bottomRightY , 0.0 ) )
{
}

TestBlocks::~TestBlocks()
{
}

unsigned int TestBlocks::GetTextureId()
{
	return -1;
}

void TestBlocks::Draw()
{
	glColor3d( 0.0 , 1.0 , 0.0 );
	WorldObject::Draw();
}

bool TestBlocks::DetectCollision( GameDude * dude )
{
	double aR = dude->GetBottomRightPoint().x;
	double aL = dude->GetTopLeftPoint().x;
	double bR = m_bottomRightPoint.x;
	double bL = m_topLeftPoint.x;
	if( ( aR <= bR && aR >= bL ) || ( aL <= bR && aL >= bL ) || ( bL <= aR && bL >= aL ) || ( bR <= aR && bR >= aL ) )
	{
		return true;
	}
	return false;
}