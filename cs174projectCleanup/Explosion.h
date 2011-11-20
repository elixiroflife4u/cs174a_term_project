#ifndef _EXPLOSION
#define _EXPLOSION

#include "GameEntity.h"

class Explosion:public GameEntity{
private:
	float _maxRadius;
	int _frameTime;
	int _currTime;
	bool _harmless;
	float _damagePerFrame;
public:
	Explosion(float maxRadius=3.0, int frameTime=4, float damagePerFrame=0.0)
		:GameEntity(ID_EXPLOSION),_maxRadius(maxRadius),_frameTime(frameTime),_currTime(0),_harmless(false),_damagePerFrame(damagePerFrame)
	{
		setModel(DrawableEntity(NULL,"Resources/sphere.obj"));
		scale(0,0,0);
		getModel().setDiffuseColor(1,1,1);
		getModel().setHighlightColor(.5,.5,.5);
	}

	void update(){
		float scaleVal=((float)_currTime/_frameTime);
		float radiusVal=scaleVal*_maxRadius+3;
		setScale(radiusVal,radiusVal,radiusVal);
		getModel().setAlpha((1-scaleVal)*1);

		if((_currTime/_frameTime)>.5){
			_harmless=true;
		}
		if(_currTime>_frameTime){
			this->setDelete();
		}

		_currTime++;
	}

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