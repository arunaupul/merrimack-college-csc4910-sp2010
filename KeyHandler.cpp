#include "KeyHandler.h"
#include <cstring>

KeyHandler::KeyHandler()
{
}

bool KeyHandler::GetPressed( const unsigned int & keyNumber )
{
	return ( keyNumber < MAX_KEYS ? m_keys[keyNumber] : false );
}

void KeyHandler::SetPressed( const unsigned int & keyNumber )
{
	if( keyNumber < MAX_KEYS )
	{
		m_keys[keyNumber] = true;
	}
}

void KeyHandler::SetReleased( const unsigned int &keyNumber )
{
	if( keyNumber < MAX_KEYS )
	{
		m_keys[keyNumber] = false;
	}
}

void KeyHandler::Reset()
{
	memset( &m_keys , 0 , sizeof( bool ) * MAX_KEYS );
}
