/**
 * @file GameBase.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Primary class for the game.
 * This is the primary class to control the program
 *
 */
#ifndef _GAME_BASE_H_
#define _GAME_BASE_H_

#include <list>

#include "GlApplication.h"
#include "WorldObject.h"
#include "GameDude.h"
#include "GameEnums.h"
#include "ControlObject.h"
#include "Menu.h"

/**
 * @class GameBase
 * @brief Primary Game Class
 *
 * Primary class for the game.
 * This is the primary class to control the program
 */
class GameBase : public GlApplication {
public:
	/**
	 * Constructor
	 */
	GameBase();

	/**
	 * Destructor
	 */
	virtual ~GameBase();

	/**
	 * Overriden Method to perform required game setup
	 * @return True is everything Initilized properly
	 */
	virtual bool PerformInit();

	/**
	 * Overriden Method to handle key press events
	 * @param key The code of the pressed key
	 */
	virtual void KeyPressed( unsigned int key );

	/**
	 * Overriden Method to handle key release events
	 * @param key The code of the released key
	 */
	virtual void KeyReleased( unsigned int key );

	/**
	 * Custom update method to update the game objects
	 * @param currentTick The current tick count
	 */
	virtual void PerformUpdate( int currentTick );

	/**
	 * Method to start the game
	 */
	void PlayGame();

	/**
	 * Custom method to draw the game objects
	 */
	void Draw();

	/**
	 * Event handler for Left Mouse Click Events
	 * @param clickedPoint Point the mouse clicked on
	 */
	virtual void LeftMouseClick( Point & clickedPoint );
private:
	/**
	 * Builds the font used in the HUD and Menus
	 */
	void BuildHUDFont();

	/**
	 * Cleans up the font used in the HUD and Menus
	 */
	void KillHudFont();

	/**
	 * List of worlds to use in the current game
	 */
	std::list<WorldObject *> m_worldList;

	/**
	 * The current game world the player is on
	 */
	std::list<WorldObject *>::iterator m_currentWorld;

	/**
	 * The player's character
	 */
	GameDude * m_gameDude;

	/**
	 * The current running state of the game
	 */
	GameState m_currentGameState;

	/**
	 * Base offset of the hud text
	 */
	unsigned int m_hudTextBase;
	GLYPHMETRICSFLOAT m_hudTextGmf[256];

	/**
	 * Control object for the player's controls
	 */
	ControlObject * m_controls;

	/**
	 * Main menu
	 */
	Menu * m_menu;

	/**
	 * Timer used to delay the players special ability
	 */
	int m_delayTimer;
};

#endif /* _GAME_BASE_H_ */