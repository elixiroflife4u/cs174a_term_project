#ifndef _COLLISIONBOX
#define _COLLISIONBOX

#include "WorldEntity.h"

class CollisionBox:private WorldEntity{
private:
	vec3 _dimensions;
public:
	bool didCollide(CollisionBox b);

	void setDim(float x, float y, float z);
	void setDim(vec3 d);
	void setTranslate(float x,float y, float z);
	void setTranslate(vec3 v);

	vec3 getPoint1() const;
	vec3 getPoint2() const;
};

#endif //_COLLISIONOBJECT