#include "MenuItem.h"

#include <windows.h>
#include <gl\gl.h>

MenuItem::MenuItem( const std::wstring & text , Square pos , int id , unsigned int textBase )
:	m_position( pos ),
	m_menuId( id ),
	m_text( text ),
	m_textBase( textBase )
{
}

MenuItem::~MenuItem()
{
}

bool MenuItem::ContainPoint( const Point & point )
{
	if( point.x >= m_position.left && point.x <= m_position.right &&
		point.y >= m_position.bottom && point.y <= m_position.top )
	{
		return true;
	}
	return false;
}

int MenuItem::GetId()
{
	return m_menuId;
}

void MenuItem::Draw()
{
	double leftX = ( m_position.right - m_position.left ) / 2 + m_position.left - ( m_text.length() / 2 * .5 );
	double bottomY = ( m_position.top - m_position.bottom ) / 2 + m_position.bottom - .2;
	glColor4d( 0.0 , 0.0 , 0.0 , 0.0 );
	glBegin( GL_POLYGON );
		glVertex3d( m_position.left , m_position.bottom , 0.0 );
		glVertex3d( m_position.left , m_position.top , 0.0 );
		glVertex3d( m_position.right , m_position.top , 0.0 );
		glVertex3d( m_position.right , m_position.bottom , 0.0 );	
	glEnd();
	glColor3d( 1.0 , 1.0 , 1.0 );
	glTranslated( leftX , bottomY , 0.0 );
	glPushAttrib( GL_LIST_BIT );
	glListBase( m_textBase );
	glCallLists( m_text.length() , GL_UNSIGNED_SHORT , m_text.c_str() );
	glPopAttrib();
}