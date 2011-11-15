#ifndef _COLLISIONBOX
#define _COLLISIONBOX

#include "WorldEntity.h"

class CollisionBox:public WorldEntity{
private:
	vec3 _dimensions;
public:
	/** @brief Constructs a new CollisionBox Object
	 */
	CollisionBox();
	/** @brief Returns true if this box intersects with the passed Collision box b
	 */
	bool didCollide(const CollisionBox& b) const;

	/** @brief Sets the dimensions of the box
	 */
	void setDim(float x, float y, float z);
	void setDim(vec3 d);

	/** @brief Allows access to the WorldEntity Translate functions
	 */
	void setTranslate(float x,float y, float z);
	void setTranslate(vec3 v);
	/** @brief Allows access to the WorldEntity setParent function
	 */
	inline void setParent(const WorldEntity* p){WorldEntity::setParent(p);}

	/** @brief Returns the point far top right and far top left points of the box
	 */
	vec3 getPoint1() const;
	vec3 getPoint2() const;
	vec3 getDimensions()const {return _dimensions*getScale();}
};

#endif //_COLLISIONOBJECT