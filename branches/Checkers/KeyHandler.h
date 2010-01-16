#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

#define MAX_KEYS 256

class KeyHandler
{
public:
	// Constructor
	KeyHandler();

	// Releases all keys
	void Reset();

	// Sets a key as pressed
	void SetPressed( const unsigned int & keyNumber );

	// Sets a ket as released
	void SetReleased( const unsigned int & keyNumber );

	// Gets the status of a key
	bool GetPressed( const unsigned int & keyNumber );
private:
	bool m_keys[ MAX_KEYS ];
};

#endif /* _KEY_HANDLER_H_ */