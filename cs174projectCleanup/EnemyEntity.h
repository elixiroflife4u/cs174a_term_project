#ifndef _ENEMYENTITY
#define _ENEMYENTITY

#include "MobileEntity.h"

//UNUSED CLASS
class EnemyEntity:public MobileEntity{
private:
public:
	Enemyentity()
		:MobileEntity(0) //must be changed to proper entity type
	{}

	void update(){}
	void onCollide(){}

}



#endif //_ENEMYENTITY