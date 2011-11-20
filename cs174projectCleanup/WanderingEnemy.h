#ifndef WANDERING_ENEMY_H
#define WANDERING_ENEMY_H

#include "MobileEntity.h"

class WanderingEnemy : public MobileEntity {
private:
	int _wanderCount;
public:
	WanderingEnemy(vec3 pos = vec3(0,0,0));

	void update();
	void onCollide(const GameEntity& g);
};

#endif