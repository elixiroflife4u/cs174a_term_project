#ifndef _GRENADEBULLET
#define _GRENADEBULLET

#include "BulletEntity.h"

class GrenadeEntity: public BulletEntity{
private:
	PointLight* p;
	int _lifeCount;


public:
	GrenadeEntity(vec3 pos, vec3 dir, float force=5)
		:BulletEntity(pos,20,ID_BULLET_GRENADE),_lifeCount(0)
	{
		MobileEntity::setVel(normalize(dir)*force);

		setModel(DrawableEntity(NULL,"Resources/grenade.obj"));
		scale(.75,.75,.75);
		getModel().setDiffuseColor(1,0,0);
		getModel().scale(.75,.75,.75);
		getModel().setShininess(100);
		getModel().setHighlightColor(.5,0,0);

		this->setHitbox(CollisionBox(vec3(1.5,1.5,1.5)));
		
		p=new PointLight(vec3(1,0,0),1,5);
		Globals::addLight(p);
		p->setParent(this);
	}
	~GrenadeEntity(){
		if(!Globals::deleteLight(p)){
			delete p;
		}
	}
	void update(){
		increaseVel(Globals::grav);
		translate(getVel());
		rotate(15,0,15);

		vec3 dir=Globals::getPlayer()->getTranslate()-getTranslate();
		if(dot(dir,dir)>pow(300.0,2)){
			setDelete();
		}


		_lifeCount++;

		if(_lifeCount%6<3){
			getModel().setHighlightColor(.25,0,0);
			p->setBrightness(1);
		}
		else{
			getModel().setHighlightColor(.75,0,0);
			p->setBrightness(5);
		}
	}

	void onCollide(const GameEntity& g){
	
		Explosion* e=new Explosion(5);;
		e->setTranslate(getTranslate());
		Globals::addSoftEntity(e);

		setDelete();
	}






};

#endif //_GRENADEBULLET