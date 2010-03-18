/*
 *************************
 **   Ryan Fleming      **
 **   GlFrameworkObject **
 **   Jan 27, 2010      **
 **         ,,,         **
 **        (0 0)        **
 **  ---ooO-(_)-Ooo---  **
 *************************
 * Version 1
 *
 * Base class for the Framework Objects
 */

#ifndef _GL_FRAMEWORK_OBJECT_H_
#define _GL_FRAMEWORK_OBJECT_H_

class GlFrameworkObject{
public:
	virtual void Draw() = 0;				// Method to draw the object
	virtual void Update( int ticks ) = 0;	// Mehtod to update the object
};

#endif /* _GL_FRAMEWORK_OBJECT_H_ */