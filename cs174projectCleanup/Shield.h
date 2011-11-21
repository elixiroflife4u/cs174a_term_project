#ifndef _SHIELD
#define _SHIELD

#include "GameEntity.h"

class Shield:public GameEntity{
private:
	int _currTime;
	int _lifeTime;
	int _maxSize;
public:
	Shield(vec3 pos, float maxSize, int lifetime=10,WorldEntity* p=NULL)
		:GameEntity(ID_SHIELD),_currTime(0),_maxSize(maxSize),_lifeTime(lifetime)
	{
		setParent(p);

		DrawableEntity d=DrawableEntity(NULL,"Resources/sphere.obj");
		d.setAlpha(.5);

		d.setDiffuseColor(0,0,0);
		d.setHighlightColor(0,1,.5);
		d.scale(0,0,0);
		setModel(d);
		scale(6,6,6);
	}

	void onCollide(const GameEntity& g){
		switch(g.getId()){
		case ID_BULLET_STRAIGHT:
		case ID_BULLET_GRENADE:
			getModel().setHighlightColor(1,1,0);
		}
	}

	void update(){

		float scaleFactor=((float)_currTime)/_lifeTime;
		float radiusFactor=(_maxSize)*scaleFactor+2;

		getModel().setAlpha((1-scaleFactor)*.9+.1);

		getModel().setScale(radiusFactor/6,radiusFactor/6,radiusFactor/6);

		_currTime++;
		if(_currTime>_lifeTime)setDelete();
		getModel().setHighlightColor(0,1,.5);
	}




};

#endif //_SHIELD