#ifndef _EXPLOSION
#define _EXPLOSION

#include "GameEntity.h"

/** @brief And Explosion can be created and added to the world
  * at any point. The sphere is created and then it expands
  * outward and grows more and more transparent
  *
  */

class Explosion:public GameEntity{
private:
	float _maxRadius;
	int _frameTime;
	int _currTime;
	bool _harmless;
	float _damagePerFrame;
public:
	/** @brief Initializes the explosion object */
	Explosion(float maxRadius=3.0, int frameTime=4, float damagePerFrame=0.0)
		:GameEntity(ID_EXPLOSION),_maxRadius(maxRadius),_frameTime(frameTime),_currTime(0),_harmless(false),_damagePerFrame(damagePerFrame)
	{
		setModel(DrawableEntity(NULL,"resources/sphere.obj"));
		scale(0,0,0);
		getModel().setDiffuseColor(1,1,1);
		getModel().setHighlightColor(.5,.5,.5);
		getModel().setNormalMap("resources/floorNormal.jpg");
		getModel().setNormalMapDepth(.1);
	}
	/** @brief Updates the entity to expand and become more transparent over time
	*/
	void update(){
		float scaleVal=((float)_currTime/_frameTime);
		float radiusVal=scaleVal*_maxRadius+3; ///calculates the scale modifier based off of the current time vs life time
		setScale(radiusVal,radiusVal,radiusVal);
		getModel().setAlpha((1-scaleVal)*.6);

		//if it has been long enough, the explosion should be harmless
		if((_currTime/_frameTime)>.5){
			_harmless=true;
		}
		//if the life time has been exhausted, then delete the object
		if(_currTime>_frameTime){
			this->setDelete();
		}
		_currTime++;
	}
	/** @brief returns the damage that the object is supposed to do */
	float getDamage(){
		if(!_harmless){
			return _damagePerFrame;
		}
		else{
			return 0;
		}
	}
	void onCollide(const GameEntity& g){}

};

#endif //_EXPLOSION