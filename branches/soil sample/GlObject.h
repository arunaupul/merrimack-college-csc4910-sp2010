#ifndef _GL_OBJECT_H_
#define _GL_OBJECT_H_

class GlObject
{
public:
	virtual void Draw() = 0;
	virtual void Update( int ticks ) = 0;
};

#endif /* _GL_OBJECT_H_ */