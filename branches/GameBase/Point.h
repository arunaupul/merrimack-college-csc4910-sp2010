#ifndef _POINT_H_
#define _POINT_H_

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