#include "WanderingEnemy.h"
#include "World.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

WanderingEnemy::WanderingEnemy(vec3 pos) : MobileEntity(ID_WANDERING_EMEMY), _wanderCount(0) {
	translate(pos);
	setModel(DrawableEntity(NULL,"Resources/cube.obj"));
	scale(3,5,3);
}

void WanderingEnemy::update() {
	static const float MAX_VEL=1;
	static const int WANDER_COUNT = 60;

	//Add gravity effect
	increaseVel(Globals::grav);

	//Choose destination randomly
	if(!_wanderCount) {
		//rand() doesn't seem to work well for floating point numbers,
		//so we'll choose an integral degree and convert it to radians.
		const double xz = (std::rand() % 360) / 180.0 * M_PI;
		const vec3 direction(cos(xz), 0, sin(xz));
		setAcc(direction);

		_wanderCount = WANDER_COUNT;
	} else
		_wanderCount--;

	//Actuate acceleration
	increaseVel(getAcc());

	//Limit velocity and set it
	vec3 horizVel=getVel();
	horizVel.y=0;
	if(dot(horizVel,horizVel)>pow(MAX_VEL,2)){
		horizVel=normalize(horizVel)*MAX_VEL;
		setVelX(horizVel.x);
		setVelZ(horizVel.z);
	}
	translate(getVel());
}
void WanderingEnemy::onCollide(const GameEntity& g){
	switch(g.getId()) {
	case ID_WALL:
	case ID_ENEMY_TURRET:
	case ID_WANDERING_EMEMY:
	case ID_PLAYER:
		MobileEntity::placeAtEdge(g);
		break;
	case ID_BULLET_STRAIGHT:
	case ID_BULLET_GRENADE:
		///@todo Implement.
		break;
	}
}