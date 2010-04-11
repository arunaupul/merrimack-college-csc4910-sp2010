/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * Base class for the Framework Objects
 *
 */

#ifndef _GL_FRAMEWORK_OBJECT_H_
#define _GL_FRAMEWORK_OBJECT_H_

/**
 * @class GlFrameworkObject
 * @brief Interface for objects to interact with GlApplication
 *
 * Base class for the Framework Objects
 */
class GlFrameworkObject{
public:
	/**
	 * Method to draw the object
	 */
	virtual void Draw() = 0;

	/**
	 * Method to update the object 
	 * @param ticks Number of ticks passed since the last call to update
	 */
	virtual void Update( int ticks ) = 0;
};

#endif /* _GL_FRAMEWORK_OBJECT_H_ */