/**
 * @file
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

class BackGroundManager
{
public:
	BackGroundManager( const std::wstring & backgroundPath , double screenWidth , double screenHeight , double backgroundCameraPercent );
	~BackGroundManager();
	void Draw( double xOffset );
private:
	GraphicLoaders::TextureIdentifier m_background;
	double m_screenWidth;
	double m_screenHeight;
	double m_cameraPercent;
};

#endif /* _BACK_GROUND_MANAGER_H_ */