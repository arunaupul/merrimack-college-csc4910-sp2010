/**
 * @file
 * @author	Ryan Fleming <rfleming71@gmail.com>
 * @version 1.0
 *
 * This file contains the majority of the enums
 * used throught the game
 *
 */
#ifndef _GAME_ENUMS_H_
#define _GAME_ENUMS_H_

/**
 * @enum CollisionSideEnum
 * Used in the collision detection system.
 * Used to indicate which side of an object has been collided with
 */
enum CollisionSideEnum {
	CS_TOP = 0,
	CS_RIGHT = 1,
	CS_BOTTOM = 2,
	CS_LEFT = 3
};

/**
 * @enum GameDudeStatus
 * This enum represents the current state of the player
 * character within the game
 */
enum GameDudeStatus {
	GDS_DEAD = 0,
	GDS_SMALL = 1,
	GDS_BIG = 2,
	GDS_SPECIAL = 3
};

/**
 * @enum HoriztonalStatus
 * Used to represent an objects current horizontal movement
 */
enum HoriztonalStatus {
	HS_LEFT = 0,
	HS_NONE = 1,
	HS_RIGHT = 2
};

/**
 * @enum VerticalStatus
 * Used to represent an objects current vertical movement
 */
enum VerticalStatus {
	VS_JUMPING = 0,
	VS_NONE = 1,
	VS_FALLING = 2
};

/**
 * @enum GameObjects
 * Used to track object id used in the game loader
 * each id allows a given game object to be loaded into a level
 */
enum GameObjects {
	GO_BRICK_BLOCK = 0,
	GO_AI_TYPE1 = 1,
	GO_AI_TYPE2 = 2,
	GO_PIPE = 3,
	GO_LEVEL_END = 4,
	GO_SPECIAL_BLOCK = 5
};

/**
 * @enum GameState
 * This enum tracks the current action the game is performing
 */
enum GameState {
	GS_STARTING_MENU = 0,
	GS_OPTIONS_MENU = 1,
	GS_PAUSE_MENU = 2,
	GS_GAME_PLAYING = 3,
	GS_PLAYER_DEAD = 4,
	GS_GAME_CREDITS = 5,
	GS_QUITING = 6
};

/**
 * @enum ScoreObject
 * Used to track each object when it adds to the players score
 */
enum ScoreObject {
	SO_AI_TYPE_1 = 0,
	SO_AI_TYPE_2 = 1,
	SO_LEVEL_END = 2
};

/**
 * @enum StartMenuItem
 * Used to unquiely ID each option located in the starting menu
 */
enum StartMenuItem {
	SMI_NEW_GAME = 0,
	SMI_LOAD_GAME = 1,
	SMI_OPTIONS = 2,
	SMI_QUIT = 3,
	SMI_INVALID = -1
};

#endif /* _GAME_ENUMS_H_ */