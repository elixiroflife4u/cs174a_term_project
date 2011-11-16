#ifndef GUARD_BULLETENTITY_H
#define GUARD_BULLETENTITY_H

#include "MobileEntity.h"

class BulletEntity: public MobileEntity{
protected:
	//the direction
	vec3 currentDirection;
	float bulletDamage;
public:
	//some contructor taking a vec3 of starting
	BulletEntity(vec3 startPosition, vec3 startDirection, float damage, unsigned int id) 
		: MobileEntity(id), currentDirection(normalize(startDirection)), bulletDamage(damage)
	{
		WorldEntity::setTranslate(startPosition.x, startPosition.y, startPosition.z);
		//the inheriting class takes care of setting the acceleration and the velocity.
	}
	/** @brief Updates the state of the object every frame. 
	  * Must be provided by subclasses. */
	virtual void update() = 0;
	/** @brief What to do on a collision. 
	  * Must be provided by subclasses. */
	virtual void onCollide(const GameEntity& g)=0;
	/** @brief Gets the bullet damage factor. */
	float getBulletDamage() const { return bulletDamage; }
};
#endif