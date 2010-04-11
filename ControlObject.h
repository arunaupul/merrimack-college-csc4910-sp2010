/**
 * @file ControlObject.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Contains all relevant code for user configurable controls
 */

#ifndef _CONTROL_OBJECT_H_
#define _CONTROL_OBJECT_H_

#include <string>

/**
 * @enum Controls
 * Unqiuely ids each control the player can use
 */
enum Controls {
	CO_RIGHT = 0,
	CO_LEFT = 1,
	CO_JUMP = 2,
	CO_CROUCH = 3,
	CO_PAUSE = 4,
	CO_USE_SPECIAL = 5,
	CO_MAX_CONTROL
};

/**
 * @class ControlObject
 * @brief Keyboard Control Manager
 *
 * Utility Object to manage user configured controls
 * for the game
 */
class ControlObject {
public:
	/**
	 * Constructor
	 */
	ControlObject();

	/**
	 * Destructor
	 */
	virtual ~ControlObject();

	/**
	 * Obtains the keyboard key number for a given control
	 * @param control Control Id of the command to obtain
	 * @return Keyboard code for the command
	 */
	unsigned int GetControlKey( Controls control );

	/**
	 * Sets the control key for a given control
	 * @param control Control to configure
	 * @param key New key to map to the control
	 */
	void SetControlKey( Controls control , unsigned int key );

	/**
	 * Loads a config file for the control set
	 * @param fileName File Path to the control file
	 */
	void LoadControls( const std::wstring & fileName );

	/**
	 * Converts a string into the predefined keyboard codes
	 * @param keyString Key to convert
	 * @return Keyboard code for the string
	 */
	unsigned int StringToKey( const std::string * keyString );
private:
	/**
	 * Array to maintain maps between a given control and the key
	 */
	unsigned int m_controlKeys[CO_MAX_CONTROL];
};

#endif /* _CONTROL_OBJECT_H_ */