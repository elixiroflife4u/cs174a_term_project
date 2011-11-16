#ifndef guard_straightbulletentity_h
#define guard_straightbulletentity_h
#include "BulletEntity.h"
class StraightBulletEntity: public BulletEntity
{
private:
	int numOfAcclUpdates;

public:
	/** @brief the straight bullet types will have the id defined  GameEntity.h
	* All straight bullets will take the accel and  initial velocity, 
	* and multiply them with initial direction before storing them.
	* @param numberOfAcclUpdates is the number of frames for which the bullet will accelerate for.
	*/
	StraightBulletEntity(float accelMag, float initialVelMag, vec3 direction, 
		vec3 startPosition, float damage, int numberOfAcclUpdates)
		: BulletEntity(startPosition, direction, damage, 2), numOfAcclUpdates(numberOfAcclUpdates)
	{
		///@todo give this bullet type an id in the GameEntity.h and then compile
		MobileEntity::setAcc(accelMag*currentDirection);
		MobileEntity::setVel(initialVelMag*currentDirection);

		///@todo Create and set an actual bullet model.
		GameEntity::setModel(DrawableEntity(NULL,"Resources/cube.obj",this));
	}
	/** @brief update the position of the bullet. the bullet accelerates for numOfAcclUpdate updates
	* before switching to a constant velocity. Each update adds the acc to current vel which is then 
	* added to the current position. 
	*/
	void update()
	{
		if(!numOfAcclUpdates)
			MobileEntity::setAcc(0*currentDirection);
		
		MobileEntity::setVel(MobileEntity::getAcc()+MobileEntity::getVel());
		WorldEntity::translate(MobileEntity::getVel());

		if(numOfAcclUpdates)
			numOfAcclUpdates--;
	}
	void onCollide(const GameEntity& g)
	{
		///@todo implement
		throw new CException("function not implemented!");
	}
};
#endif