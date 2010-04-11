/**
 * @file Point.h
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * This file contains the struct that represents a point
 * openGL space
 *
 * @todo Merge this file into GameStructs
 */
#ifndef _POINT_H_
#define _POINT_H_

/**
 * @struct Point
 * Represents a single point in openGL space
 */
struct Point
{
	Point( double x = 0.0 , double y = 0.0 , double z = 0.0 )
	{
		this->x = x;
		this->y = y;
		this->z = z;
	};
	double x;
	double y;
	double z;
};

#endif /* _POINT_H_ */