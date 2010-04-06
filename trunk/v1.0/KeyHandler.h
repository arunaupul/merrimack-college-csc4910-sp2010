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

#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

#define MAX_KEYS 256

class KeyHandler
{
public:
	KeyHandler();											// Constructor
	void Reset();											// Releases all keys
	void SetPressed( const unsigned int & keyNumber );		// Sets a key as pressed
	void SetReleased( const unsigned int & keyNumber );		// Sets a key as released
	bool GetPressed( const unsigned int & keyNumber );		// Gets the status of a key
private:
	bool m_keys[ MAX_KEYS ];
};

#endif /* _KEY_HANDLER_H_ */