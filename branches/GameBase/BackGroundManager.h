/**
 * @file BackGroundManager.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Class to manage which section of the background image
 * to display to the user.
 *
 */
#ifndef _BACK_GROUND_MANAGER_H_
#define _BACK_GROUND_MANAGER_H_

#include "GraphicLoaders.h"
#include <string>

/**
 * @class BackGroundManager 
 * @brief Displays the background of the game
 *
 * Class to manage which section of the background image
 * to display to the user.
 */
class BackGroundManager
{
public:
	/**
	 * Constructor
	 * @param backgroundPath Path to the background image to load
	 * @param screenWidth Width of the screen in openGL units
	 * @param screenHeight Height of the screen in openGL units
	 * @param backgroundCameraPercent Percentage of the image to display at any one given time
	 */
	BackGroundManager( const std::wstring & backgroundPath , double screenWidth , double screenHeight , double backgroundCameraPercent );

	/**
	 * Desctructor
	 */
	~BackGroundManager();

	/**
	 * Method to draw the background image
	 * @param xOffset Distance the left side of the screen is from the start of the level
	 */
	void Draw( double xOffset );
private:
	/**
	 * Image id of the background image
	 */
	GraphicLoaders::TextureIdentifier m_background;

	/**
	 * Width of the screen in openGL Units
	 */
	double m_screenWidth;
	
	/**
	 * Height of the screen in openGL Units
	 */
	double m_screenHeight;

	/**
	 * Percentage of the image to display at any one given time
	 */
	double m_cameraPercent;
};

#endif /* _BACK_GROUND_MANAGER_H_ */