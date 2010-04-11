/**
 * @file KeyHandler.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Class manage which keys are currently being pressed
 *
 */

#ifndef _KEY_HANDLER_H_
#define _KEY_HANDLER_H_

/**
 * Maximum number of keys to handle
 */
#define MAX_KEYS 256

/**
 * @class KeyHandler
 * @brief Manages key presses
 *
 * Class manage which keys are currently being pressed
 */
class KeyHandler {
public:
	/**
	 * Constructor
	 */
	KeyHandler();

	/**
	 * Releases all keys
	 */
	void Reset();

	/**
	 * Sets a key as pressed
	 * @param keyNumber Key to set pressed
	 */
	void SetPressed( const unsigned int & keyNumber );

	/**
	 * Sets a key as released
	 * @param keyNumber Key to set released
	 */
	void SetReleased( const unsigned int & keyNumber );

	/**
	 * Gets the status of a key
	 * @param keyNumber The key number to check
	 * @return Status of the key
	 */
	bool GetPressed( const unsigned int & keyNumber );
private:

	/**
	 * Array to track key presses
	 */
	bool m_keys[ MAX_KEYS ];
};

#endif /* _KEY_HANDLER_H_ */