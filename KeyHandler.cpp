/*
 *************************
 **   Ryan Fleming      **
 **   KeyHandler        **
 **   Jan 27, 2010      **
 **         ,,,         **
 **        (0 0)        **
 **  ---ooO-(_)-Ooo---  **
 *************************
 * Version 1
 *
 * Class manage which keys are currently being pressed
 */

#include "KeyHandler.h"
#include <cstring>

// Constructor
KeyHandler::KeyHandler()
{
	Reset();					// Default to all keys released
}

// Gets the status of a key
bool KeyHandler::GetPressed( const unsigned int & keyNumber )
{
	// If the key requested is outside the array range, default to false
	return ( keyNumber < MAX_KEYS ? m_keys[keyNumber] : false );
}

// Sets a key as pressed
void KeyHandler::SetPressed( const unsigned int & keyNumber )
{
	if( keyNumber < MAX_KEYS )
	{
		m_keys[keyNumber] = true;
	}
}

// Sets a key as released
void KeyHandler::SetReleased( const unsigned int &keyNumber )
{
	if( keyNumber < MAX_KEYS )
	{
		m_keys[keyNumber] = false;
	}
}

// Releases all keys
void KeyHandler::Reset()
{
	memset( &m_keys , 0 , sizeof( bool ) * MAX_KEYS );
}
