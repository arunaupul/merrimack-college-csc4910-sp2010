/**
 * @file RgbaColor.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * File contains the struct to represent an openGL color
 *
 * @todo Merge this file into GameStructs.h
 */
#ifndef _RGBA_COLOR_H_
#define _RGBA_COLOR_H_

/**
 * @struct RgbaColor
 * @brief OpenGL Color
 *
 * Struct represents the 4 values of an openGL using 
 * 4 unsigned bytes
 */
struct RgbaColor
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};

#endif /* _RGBA_COLOR_H_ */