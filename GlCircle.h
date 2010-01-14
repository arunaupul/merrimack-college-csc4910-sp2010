#ifndef _GL_CIRCLE_H_
#define _GL_CIRCLE_H_

#include "Point.h"
#include "RgbaColor.h"

class GlCircle
{
public:
	GlCircle( float radius , Point center , RgbaColor color );
	~GlCircle();
	void Draw();
	bool ContainsPoint( Point point );
private:
	float m_radius;
	Point m_center;
	RgbaColor m_color;
};

#endif /* _GL_CIRCLE_H_ */