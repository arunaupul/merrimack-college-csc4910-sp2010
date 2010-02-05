#ifndef _WORLD_OBJECT_H_
#define _WORLD_OBJECT_H_

#include "Point.h"
#include "GraphicLoaders.h"
#include "CollisionObject.h"

class WorldObject : public CollisionObject
{
public:
	WorldObject( Point topLeft , Point bottomRight );
	virtual bool ObjectOnScreen( double leftBound , double rightBound );
	virtual void Draw();
	virtual GraphicLoaders::TextureIdentifier GetTextureId() = 0;
protected:
	Point m_topLeftPoint;
	Point m_bottomRightPoint;
};

#endif /* _WORLD_OBJECT_H_ */