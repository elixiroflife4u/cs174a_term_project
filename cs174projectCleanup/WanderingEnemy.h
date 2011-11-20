#ifndef WANDERING_ENEMY_H
#define WANDERING_ENEMY_H

#include "MobileEntity.h"

class WanderingEnemy : public MobileEntity {
private:
	int _wanderCount;

	static const int WANDER_COUNT = 60;
	static const double FOV, ///< The entities field of view in the XZ plane (infitine elsewhere).
	                    MIN_DISTANCE, ///< If closer to player than this, it will fire but not translate.
	                    MAX_DISTANCE; ///< If farther from player than this, it will ignore the player.

	void wander();
	void lockOnPlayer(double xz, double distance);
public:
	WanderingEnemy(vec3 pos = vec3(0,0,0));

	void update();
	void onCollide(const GameEntity& g);
};

#endif