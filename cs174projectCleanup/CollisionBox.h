#ifndef _COLLISIONBOX
#define _COLLISIONBOX

#include "WorldEntity.h"

/** The CollisionBox represents an object's hit box and provides
  * collision detection between two such boxes.
  *
  * As a WorldEntity, the box's positon and orientation is controlled
  * through the WorldEntity interface.
  */
class CollisionBox:public WorldEntity{
private:
	vec3 _dimensions; ///< Dimensions of the box.
public:
	/** @brief Constructs a new CollisionBox Object
	  * @param dim The dimensions of the box before into consideration
	  *  its WorldEntity scale or other transformations.
	  */
	CollisionBox(vec3 dim=vec3(1,1,1));
	/** @brief Returns true if this box intersects with the passed Collision box b
	 */
	bool didCollide(const CollisionBox& b) const;

	/** @brief Sets the dimensions of the box */
	void setDim(float x, float y, float z);
	/** @brief Sets the dimensions of the box */
	void setDim(vec3 d);

	/** @see WorldEntity::setTranslate(float, float, float) */
	void setTranslate(float x,float y, float z);
	/** @see WorldEntity::setTranslate(vec3) */
	void setTranslate(vec3 v);
	/** @see WorldEntity::setParent() */
	inline void setParent(const WorldEntity* p){WorldEntity::setParent(p);}

	/** @brief Returns the point far top right of the box. */
	vec3 getPoint1() const;
	/** @brief Returns the point far bottom left of the box. */
	vec3 getPoint2() const;
	/** @brief Returns the dimensions of the box, taking into consideration its scale. */
	vec3 getDimensions()const {return _dimensions*getScale();}
};

#endif //_COLLISIONOBJECT