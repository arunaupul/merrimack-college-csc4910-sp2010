#ifndef _GL_CIRCLE_H_
#define _GL_CIRCLE_H_

#include "Point.h"
#include "RgbaColor.h"

class GlCircle
{
public:
	GlCircle( double radius , Point center , RgbaColor color );
	~GlCircle();
	void Draw();
	void Update( int ticks );
	bool ContainsPoint( Point point );
private:
	int m_tickCount;
	double m_radius;
	double m_startingRadius;
	Point m_center;
	RgbaColor m_color;
	bool m_direction;
};

#endif /* _GL_CIRCLE_H_ */