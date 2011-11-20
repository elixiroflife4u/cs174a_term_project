#include "WanderingEnemy.h"
#include "World.h"

#include <iostream>
#include <cstdlib>
#include <cmath>

WanderingEnemy::WanderingEnemy(vec3 pos) : MobileEntity(ID_WANDERING_EMEMY), _wanderCount(0), _bulletDelay(BULLET_DELAY) {
	translate(pos);
	setModel(DrawableEntity(NULL,"Resources/cube.obj"));
	setModel(DrawableEntity(NULL,"Resources/cube.obj"),1);
	DrawableEntity& nose = getModel(1);
	nose.setScale(1/3.0, .2, 1/3.0);
	nose.translate(2/3.0, 0, 0);
	scale(3,5,3);
}

template <typename T>
static inline T clamp(T val, T min, T max) {
	return std::max(std::min(val, max), min);
}

/** Returns the next angle that an object should face at
  * if its turning rate is limited.
  * @param The current angle in degrees.
  * @param The desired angle in degrees.
  * @param The maximal difference between the current and next angle.
  * @return The next angle.
  */
static double nextDegree(double current, double desired, double max) {
	double delta = desired - current;
	if(delta > 180)
		delta -= 360;
	else if(delta < -180)
		delta += 360;

	const double limited = clamp(delta, -max, max);
	double newAngle = current + limited;
	if(newAngle < 0) newAngle += 360;
	else if(newAngle > 360) newAngle -= 360;
	return newAngle;
}

void WanderingEnemy::wander() {
	//We aren't locked on right now, so reset bullet timer.
	_bulletDelay = BULLET_DELAY;

	//Choose destination randomly
	if(!_wanderCount) {
		//rand() doesn't seem to work well for floating point numbers,
		//so we'll choose an integral degree and convert it to radians.
		_desiredHeading = (std::rand() % 360);
		const double xz = _desiredHeading * DegreesToRadians;
		const vec3 direction(cos(xz), 0, -sin(xz));
		setAcc(direction);

		_wanderCount = WANDER_COUNT;
	} else
		_wanderCount--;

	getModel().setDiffuseColor(0,0,1);
}

void WanderingEnemy::lockOnPlayer(double xz, double distance, double currentXZ) {
	_desiredHeading = xz / DegreesToRadians;

	//Move in the direction of the player.
	//(Not the current rotation because that would cause
	// the relative heading to change, which makes the movement
	// erratic.)
	//Or freeze if too close.
	if(distance > MIN_DISTANCE)	setAcc(cos(xz), 0, -sin(xz));
	else setAcc(0, 0, 0);
	_wanderCount = 0;

	//Fire!
	const vec4 local(1,0,0,0); //The enemy always fires from its local +X direction.
	const vec4 direction = RotateY(currentXZ) * local;
	const vec3 dirNorm = normalize(vec3(direction.x, direction.y, direction.z));
	if(!_bulletDelay) {
		Globals::addBullet(ID_BULLET_STRAIGHT,0,1, dirNorm, getModel(1).getTranslate() + 4*dirNorm);

		_bulletDelay = BULLET_DELAY;
	} else
		_bulletDelay--;

	//Set locked-on color.
	getModel().setDiffuseColor(1,0,0);
}

const double WanderingEnemy::FOV = 45 * DegreesToRadians;
const double WanderingEnemy::MIN_DISTANCE = 15;
const double WanderingEnemy::MAX_DISTANCE = 50;
const double WanderingEnemy::MAX_ROTATE = 5;

void WanderingEnemy::update() {
	static const float MAX_VEL = .5;

	//Check if player is within "sight"
	//The enemy has a FOV radian field-of-view on
	//the XZ plane. This calculation is independent of
	//altitude (Y).
	const Player* const player = Globals::getPlayer();
	const double currentXZ = getRotate().y;
	if(player) {
		const vec3 toPlayer = player->getTranslate() - getTranslate();
		const double distance = length(toPlayer);

		//The MIN_DISTANCE is tested in lockOnPlayer since
		//we still want to lock on, just not translate.
		if(distance < MAX_DISTANCE) {
			const double xz = std::atan2(-toPlayer.z, toPlayer.x);
			double xzDelta = (currentXZ * DegreesToRadians) - xz;
			if(xzDelta < 0) xzDelta += 2*M_PI;
			else if(xzDelta > 2*M_PI) xzDelta -= 2*M_PI;

			if(xzDelta < FOV/2 || xzDelta > 2*M_PI - FOV/2)
				lockOnPlayer(xz, distance, currentXZ);
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

	//Move towards desired heading
	setRotate(0, nextDegree(currentXZ, _desiredHeading, MAX_ROTATE), 0);

	//Check health
	if(getHealth()<0){
		setDelete();
		Explosion* e = new Explosion(6,50);
		e->translate(getTranslate());
		Globals::addSoftEntity(e);
	}

	resetHightlight();
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
		decHealth(1);
		break;
	case ID_BULLET_GRENADE:
		decHealth(5);
		break;
	case ID_EXPLOSION:
		decHealth(1);
		break;
	}
}