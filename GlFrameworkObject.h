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

class GlFrameworkObject{
public:
	virtual void Draw() = 0;				// Method to draw the object
	virtual void Update( int ticks ) = 0;	// Mehtod to update the object
};

#endif /* _GL_FRAMEWORK_OBJECT_H_ */