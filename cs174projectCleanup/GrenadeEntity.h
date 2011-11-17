#ifndef _GRENADEBULLET
#define _GRENADEBULLET

#include "BulletEntity.h"

class GrenadeEntity: public BulletEntity{
private:
public:
	GrenadeEntity(vec3 pos, vec3 dir, float force=5)
		:BulletEntity(pos,20,ID_BULLET_GRENADE)
	{
		MobileEntity::setVel(normalize(dir)*force);

		setModel(DrawableEntity(NULL,"Resources/test.obj"));
		scale(.75,.75,.75);
		getModel().setDiffuseColor(1,0,0);
		getModel().scale(.5,.5,.5);
		getModel().setShininess(100);
	}
	void update(){
		increaseVel(Globals::grav);
		translate(getVel());
		rotate(0,15,0);
	}

	void onCollide(const GameEntity& g){
	
		Explosion* e=new Explosion();
		e->setTranslate(getTranslate());
		Globals::addEntity(e);


	}






};

#endif //_GRENADEBULLET