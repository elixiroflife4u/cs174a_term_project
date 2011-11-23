#ifndef guard_straightbulletentity_h
#define guard_straightbulletentity_h
#include "BulletEntity.h"
/** @brief A StraightBulletEntity is a bullet that travels in a straight
  * line. It accelerates at a given constant rate for a given number
  * of frames from a given starting velocity. Afterwards, it cruises
  * at the obtained speed until it collides.
  */
class StraightBulletEntity: public BulletEntity
{
private:
	int numOfAcclUpdates; ///< Number of frames until accleration is reset to 0.

public:
	/** @brief the straight bullet types will have the id defined  GameEntity.h
	* All straight bullets will take the accel and  initial velocity, 
	* and multiply them with initial direction before storing them.
	  * @param accelMag Magnitude of the acceleration vector.
	  * @param initialVelMag Initial magnitude of the velocity vector.
	  * @param direction Direction of bullet travel.
	  * @param startPosition Initial position.
	  * @param damage Damage factor.
	  * @param numberOfAcclUpdates Number of frames until accleration is reset to 0.
	*/
	StraightBulletEntity(float accelMag, float initialVelMag, vec3 direction, 
		vec3 startPosition, float damage, int numberOfAcclUpdates)
		: BulletEntity(startPosition, damage, ID_BULLET_STRAIGHT), numOfAcclUpdates(numberOfAcclUpdates)
	{
		///@todo give this bullet type an id in the GameEntity.h and then compile
		MobileEntity::setAcc(accelMag*direction);
		MobileEntity::setVel(initialVelMag*direction);

		///@todo Create and set an actual bullet model.
		GameEntity::setModel(DrawableEntity(NULL,"Resources/sphere.obj",this));
		getModel().setDiffuseColor(1,.25,0);
		scale(.35,.35,.35);
		getModel().setHighlightColor(.5,.25,0);
	}
	/** @brief update the position of the bullet. the bullet accelerates for numOfAcclUpdate updates
	* before switching to a constant velocity. Each update adds the acc to current vel which is then 
	* added to the current position. 
	*/
	void update()
	{
		if(!numOfAcclUpdates)
			MobileEntity::setAcc(0,0,0);
		
		MobileEntity::setVel(MobileEntity::getAcc()+MobileEntity::getVel());
		WorldEntity::translate(MobileEntity::getVel());

		if(numOfAcclUpdates)
			numOfAcclUpdates--;

		vec3 dir=Globals::getPlayer()->getTranslate()-getTranslate();
		if(dot(dir,dir)>pow(300.0,2)){
			setDelete();
		}

	}
	void onCollide(const GameEntity& g)
	{
		setDelete();
	}
};
#endif