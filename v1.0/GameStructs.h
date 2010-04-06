/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * This file contains the majority of the structs
 * used throught the game
 *
 */

#ifndef _GAME_STRUCTS_H_
#define _GAME_STRUCTS_H_

/**
 * @def SQUARE_SIZE
 * This value represents the size of each game block
 */
#define SQUARE_SIZE		10.0

/**
 * @struct Square
 * Struct used to represent a regtangle within the game
 */
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