#ifndef _GAME_ENUMS_H_
#define _GAME_ENUMS_H_

enum CollisionSideEnum {
	CS_TOP = 0,
	CS_RIGHT = 1,
	CS_BOTTOM = 2,
	CS_LEFT = 3
};

enum GameDudeStatus {
	GDS_DEAD = 0,
	GDS_SMALL = 1,
	GDS_BIG = 2,
	GDS_SPECIAL = 3
};

enum HoriztonalStatus {
	HS_LEFT = 0,
	HS_NONE = 1,
	HS_RIGHT = 2
};

enum VerticalStatus {
	VS_JUMPING = 0,
	VS_NONE = 1,
	VS_FALLING = 2
};

enum GameObjects {
	GO_BRICK_BLOCK = 0,
	GO_AI_TYPE1 = 1,
	GO_AI_TYPE2 = 2,
	GO_PIPE = 3
};

#endif /* _GAME_ENUMS_H_ */