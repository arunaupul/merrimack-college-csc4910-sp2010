/**
 * @file MenuItem.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Items that appear within a menu
 *
 */
#ifndef _MENU_ITEM_H_
#define _MENU_ITEM_H_

#include <string>
#include "GameStructs.h"
#include "Point.h"

/**
 * @class MenuItem
 * @brief Items that appear within a menu
 *
 * Item used to represent menu options within a menu
 */
class MenuItem {
public:
	/**
	 * Constructor
	 * @param text Menu Option Text
	 * @param pos Position on the screen of the option
	 * @param id Id of the option
	 * @param textBase Base number of the text
	 */
	MenuItem( const std::wstring & text , Square pos , int id , unsigned int textBase );

	/**
	 * Destructor
	 */
	virtual ~MenuItem();

	/**
	 * Checks to see if a given point is on the option
	 * @param point Clicked Point to check
	 * @returns True is the point in on the option
	 */
	bool ContainPoint( const Point & point );

	/**
	 * Gets the ID of the menu option
	 * @return Menu Option Id
	 */
	int GetId();

	/**
	 * Draw the menu option
	 */
	void Draw();

	/**
	 * Sets if the option is the currently selected one
	 */
	void SetSelectStatus( bool status );
protected:
	/**
	 * Position of the option
	 */
	Square m_position;

	/**
	 * Text to display for the option
	 */
	std::wstring m_text;

	/**
	 * The id of the option
	 */
	int m_menuId;

	/**
	 * The base number for the font
	 */
	unsigned int m_textBase;

	/**
	 * If the option is selected
	 */
	bool m_selected;
};


#endif /* _MENU_ITEM_H_ */