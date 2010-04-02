#include "Menu.h"

#include <windows.h>
#include <gl\gl.h>
#include "MenuItem.h"
#include "Point.h"
#include <list>

#define INVALID_ID	-1

Menu::Menu( unsigned int textBase )
:	m_textBase( textBase ),
	m_clickedId( INVALID_ID )
{
}

Menu::~Menu()
{
	for( std::list<MenuItem *>::iterator iter = m_items.begin() ; iter != m_items.end() ; ++iter )
	{
		delete ( *iter );
	}
}

void Menu::Update( int ticks )
{
}

void Menu::Draw()
{
	glDisable( GL_TEXTURE_2D );
	for( std::list<MenuItem *>::iterator iter = m_items.begin() ; iter != m_items.end() ; ++iter )
	{
		glLoadIdentity();
		glTranslated( 0.0 , 0.0 , -20 );
		( *iter )->Draw();
	}
	glLoadIdentity();
	glTranslated( 0.0 , 0.0 , -20 );
	glEnable( GL_TEXTURE_2D );
}

void Menu::AddMenuItem( const std::wstring text , int id , const Square & pos )
{
	m_items.push_back( new MenuItem( text , pos , id , m_textBase ) );
}

int Menu::GetSelectedItemId()
{
	return m_clickedId;
}

void Menu::Click( const Point & point )
{
	m_clickedId = INVALID_ID;
	for( std::list<MenuItem *>::iterator iter = m_items.begin() ; iter != m_items.end() ; ++iter )
	{
		if( ( *iter )->ContainPoint( point ) )
		{
			m_clickedId = ( *iter )->GetId();
			break;
		}
	}
}