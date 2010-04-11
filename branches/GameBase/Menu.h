/**
 * @file Menu.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * General Menu Class
 *
 */
#ifndef _MENU_H_
#define _MENU_H_

#include "GlFrameworkObject.h"
#include "MenuItem.h"
#include "GameStructs.h"
#include <list>
#include <string>

/**
 * @class Menu
 * @brief Menu Class
 *
 * Creates and manages a general menu
 */
class Menu : public GlFrameworkObject {
public:
	/**
	 * Constructor
	 * @param textBase Base of the text to use
	 */
	Menu( unsigned int textBase );

	/**
	 * Desctructor
	 */
	~Menu();

	/**
	 * Update the menu \a ticks ticks
	 * @param ticks Number of ticks passed since the last call to update
	 */
	void Update( int ticks );

	/**
	 * Draw the menu
	 */
	void Draw();

	/**
	 * Adds an item to the menu
	 * @param text Text for the menu option
	 * @param id Number to ID the option when it is clicked
	 * @param pos Position of the option on the screen
	 */
	void AddMenuItem( const std::wstring text , int id , const Square & pos );

	/**
	 * Gets the selected item
	 * @return The selected Item Id or -1 if none selected
	 */
	int GetSelectedItemId();

	/**
	 * Handles on click on the menu
	 * @param point Point clicked
	 */
	void Click( const Point & point );

	/**
	 * Handles on key press in the menu
	 * @param key key pressed
	 */
	void HandleKey( unsigned int key );
protected:
	/**
	 * List of menu items to use
	 */
	std::list<MenuItem *> m_items;

	/**
	 * Base of the text font to use
	 */
	unsigned int m_textBase;

	/**
	 * Clicked item id
	 */
	int m_clickedId;

	/**
	 * Highlighted menu item
	 */
	std::list<MenuItem *>::iterator m_selectedItem;
};

#endif /* _MENU_H_ */