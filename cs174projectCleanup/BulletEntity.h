#ifndef GUARD_BULLETENTITY_H
#define GUARD_BULLETENTITY_H

#include "MobileEntity.h"

/** @brief The BulletEntity abstract class is the parent of
  * all bullet and projectile classes. It provides
  * an interface to get the damage a bullet causes upon
  * impact.
  */
class BulletEntity: public MobileEntity{
protected:
	float bulletDamage; ///< Damage caused on impact.
public:
	/** Constructs a new BulletEntity.
	  * @param startPosition The starting position.
	  * @param damage The damage caused to whatever the bullet hits.
	  * @param id A GameEntity id corresponding to a concrete bullet type.
	  */
	BulletEntity(vec3 startPosition, float damage, unsigned int id) 
		: MobileEntity(id), bulletDamage(damage)
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