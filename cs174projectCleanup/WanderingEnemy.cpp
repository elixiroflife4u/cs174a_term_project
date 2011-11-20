#include "WanderingEnemy.h"
#include "World.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

WanderingEnemy::WanderingEnemy(vec3 pos) : MobileEntity(ID_WANDERING_EMEMY), _wanderCount(0) {
	translate(pos);
	setModel(DrawableEntity(NULL,"Resources/cube.obj"));
	setModel(DrawableEntity(NULL,"Resources/cube.obj"),1);
	DrawableEntity& nose = getModel(1);
	nose.setScale(1/3.0, .2, 1/3.0);
	nose.translate(2/3.0, 0, 0);
	scale(3,5,3);
}

void WanderingEnemy::wander() {
	//Choose destination randomly
	if(!_wanderCount) {
		//rand() doesn't seem to work well for floating point numbers,
		//so we'll choose an integral degree and convert it to radians.
		const int xzDegrees = (std::rand() % 360);
		const double xz = xzDegrees * DegreesToRadians;
		const vec3 direction(cos(xz), 0, -sin(xz));
		setAcc(direction);
		///@todo Tween the rotation.
		setRotate(0, xzDegrees, 0);

		_wanderCount = WANDER_COUNT;
	} else
		_wanderCount--;

	getModel().setDiffuseColor(0,0,1);
}

void WanderingEnemy::lockOnPlayer(double xz, double distance) {
	///@todo Tween the rotation and slow down.
	setRotate(0, xz / DegreesToRadians, 0);
	if(distance > MIN_DISTANCE)	setAcc(cos(xz), 0, -sin(xz));
	else setAcc(0, 0, 0);
	_wanderCount = 0;

	getModel().setDiffuseColor(1,0,0);
}

const double WanderingEnemy::FOV = 45 * DegreesToRadians;
const double WanderingEnemy::MIN_DISTANCE = 7;
const double WanderingEnemy::MAX_DISTANCE = 25;

void WanderingEnemy::update() {
	static const float MAX_VEL = .5;

	//Check if player is within "sight"
	//The enemy has a FOV radian field-of-view on
	//the XZ plane. This calculation is independent of
	//altitude (Y).
	const Player* const player = Globals::getPlayer();
	if(player) {
		const vec3 toPlayer = player->getTranslate() - getTranslate();
		const double distance = length(toPlayer);

		//The MIN_DISTANCE is tested in lockOnPlayer since
		//we still want to lock on, just not translate.
		if(distance < MAX_DISTANCE) {
			const double xz = std::atan2(-toPlayer.z, toPlayer.x);
			double xzDelta = (getRotate().y * DegreesToRadians) - xz;
			if(xzDelta < 0) xzDelta += 2*M_PI;
			else if(xzDelta > 2*M_PI) xzDelta -= 2*M_PI;

			if(xzDelta < FOV/2 || xzDelta > 2*M_PI - FOV/2)
				lockOnPlayer(xz, distance);
			else
				wander();
		}
		else
			wander();
	} else
		wander();

	//Add gravity effect
	increaseVel(Globals::grav);

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