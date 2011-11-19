#ifndef _TURRETENTITY
#define _TURRETENTITY

#include "MobileEntity.h"

class TurretEntity:public MobileEntity{
private:
public:
	TurretEntity(vec3 pos=vec3(0,0,0))
		:MobileEntity(ID_ENEMY_TURRET)
	{
		translate(pos);
		setModel(DrawableEntity(NULL,"Resources/cube.obj"));
		getModel().translate(0,-1.5,0);
		getModel().scale(3,3,3);
		
		setModel(getModel(),1);
		getModel(1).setTranslate(0,1.5,0);

		CollisionBox b;
		b.setDim(3,6,3);

		this->setHitbox(b);
	}

	void update(){}
	void onCollide(const GameEntity& g){}

};



#endif //_TURRETENTITY