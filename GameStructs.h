#ifndef _GAME_STRUCTS_H_
#define _GAME_STRUCTS_H_

#define SQUARE_SIZE		8.0

struct Square
{
	Square( double top , double bottom , double left , double right )
	{
		this->top = top;
		this->bottom = bottom;
		this->left = left;
		this->right = right;
	}

	double top;
	double bottom;
	double left;
	double right;
};

#endif /* _GAME_STRUCTS_H_ */