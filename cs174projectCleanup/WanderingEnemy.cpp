#include "WanderingEnemy.h"
#include "World.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "BulletEntity.h"

WanderingEnemy::WanderingEnemy(vec3 pos) : MobileEntity(ID_WANDERING_EMEMY), _wanderCount(0), _bulletDelay(BULLET_DELAY) {
	translate(pos);
	setModel(DrawableEntity("resources/wanderingTexture.png","resources/wanderingBase.obj"));
	setModel(DrawableEntity(NULL,NULL),1);
	setModel(DrawableEntity("resources/wanderingTexture.png","resources/wanderingTop.obj"),2);
	getModel(2).setRotate(0,135,0);
	getModel().rotate(0,45,0);
	DrawableEntity& nose = getModel(1);
	scale(3,3,3);

	getModel().translate(0,-.5,0);
	getModel(1).translate(0,-.5,0);
	getModel(2).translate(0,-.5,0);
	//getModel(1).scale(1,2,1);

	CollisionBox b=CollisionBox(vec3(1.5,2.5,1.5));
	setHitbox(b);

}

/** Clamps a given value between two extremes.
  * @tparam T The type of input and output.
  * @param val Value to clamp.
  * @param min Minimum.
  * @param max Maximum.
  * @return min if val is less; max if val is greater; val otherwise.
  */
template <typename T>
static inline T clamp(T val, T min, T max) {
	return std::max(std::min(val, max), min);
}

/** Returns the next angle that an object should face at
  * if its turning rate is limited.
  * @param current The current angle in degrees.
  * @param desired The desired angle in degrees.
  * @param max The maximal difference between the current and next angle.
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

	//getModel().setDiffuseColor(0,0,1);
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
		Globals::addBullet(ID_BULLET_STRAIGHT,0,5, dirNorm, getModel(1).getTranslate() + .75*dirNorm);

		_bulletDelay = BULLET_DELAY;
	} else
		_bulletDelay--;

	//Set locked-on color.
	//getModel().setDiffuseColor(1,0,0);
}

const double WanderingEnemy::FOV = 270 * DegreesToRadians;
const double WanderingEnemy::MIN_DISTANCE = 15;
const double WanderingEnemy::MAX_DISTANCE = 50;
const double WanderingEnemy::MAX_ROTATE = 5;

void WanderingEnemy::update() {
	float MAX_VEL = 1;

	//Check if player is within "sight"
	//The enemy has a FOV radian field-of-view on
	//the XZ plane. This calculation is independent of
	//altitude (Y).
	const Player* const player = Globals::getPlayer();
	const double currentXZ = getRotate().y;
	if(player) {
		const vec3 toPlayer = player->getTranslate() - getTranslate();
		const double distance = length(toPlayer);

		if(distance > MAX_DISTANCE)MAX_VEL=.2;

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
	getModel().setRotate(0, -nextDegree(currentXZ, _desiredHeading, MAX_ROTATE), 0);
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
			placeAtEdge(g);
		break;
	case ID_BULLET_STRAIGHT:
		decHealth(dynamic_cast<const BulletEntity* >(&g)->getBulletDamage());
		break;
	case ID_BULLET_GRENADE:
		decHealth(dynamic_cast<const BulletEntity* >(&g)->getBulletDamage());
		break;
	case ID_BULLET_CURVY:
		decHealth(dynamic_cast<const BulletEntity* >(&g)->getBulletDamage());
		break;
	case ID_EXPLOSION:
		decHealth(1);
		break;
	}
}



//WANDERINGENEMY IMPLEMENTATION -- *slighly* different
void WanderingEnemy::placeAtEdge(const GameEntity& g)
{

	// collision detection for walls - so that the player can "land" on them and run into them
	// perhaps abstract it to the Mobileentity level because other mobile entities will need hit detection for walls as well

	CollisionBox b1=getHitBox();
	CollisionBox b2=g.getHitBox();

	//Tells whether or not the midpoint is at all within the mid point of the other box
	vec3 d1=b1.getTranslate()-getVel()-b1.getDimensions()/3-b2.getPoint1();
	vec3 d2=b1.getTranslate()-getVel()+b1.getDimensions()/3-b2.getPoint2();
	vec3 midDist=b1.getTranslate()-b2.getTranslate();

	bool midInX=(d1.x>0)!=(d2.x>0);
	bool midInY=(d1.y>0)!=(d2.y>0);
	bool midInZ=(d1.z>0)!=(d2.z>0);

	if(!midInX&&!midInY||
		!midInX&&!midInZ||
		!midInZ&&!midInY
		)
		return;
	


	vec3 newPos;

	//within the "x prism"
	float dir=0;
	float EASE_VAL=.05;
	float EASE_SCALE_VAL=3.0;

	//DIFFERENCE - REQUIRES !midInX
	if(midInY&&midInZ&&!midInX){
		if(midDist.x!=0)dir=midDist.x/abs(midDist.x);
		else dir=0;

		if(abs(d1.x)>b1.getDimensions().x/EASE_SCALE_VAL||abs(d2.x)>b1.getDimensions().x/EASE_SCALE_VAL)dir=0;

		if(abs(d1.x)<abs(d2.x)){
			if(getVel().x<0)
			{
				newPos.x=b2.getPoint1().x+b1.getDimensions().x/2;
			}
		}else{
			if(getVel().x>0)
			{
				newPos.x=b2.getPoint2().x-b1.getDimensions().x/2;
			}
		}
		if(newPos.x!=0){
			setTranslateX(newPos.x);
			setVelX(0);
		}
		translate(EASE_VAL*dir,0,0);
	}
	//DIFFERENCE - REQUIRES !midInY
	//within the "y prism"
	if(midInX&&midInZ&&!midInY){
		if(midDist.y!=0)dir=midDist.y/abs(midDist.y);
		else dir=0;

		if(abs(d1.y)>b1.getDimensions().y/EASE_SCALE_VAL||abs(d2.y)>b1.getDimensions().y/EASE_SCALE_VAL)dir=0;

		if(abs(d1.y)<abs(d2.y)){
			if(getVel().y<0)
			{
				newPos.y=b2.getPoint1().y+b1.getDimensions().y/2;
			}
		}else{
			if(getVel().y>0)
			{
				newPos.y=b2.getPoint2().y-b1.getDimensions().y/2;
			}
		}

		if(newPos.y!=0){
			setTranslateY(newPos.y);
			setVelY(0);
		}
		setVel(getVel()*.85);
		if(dot(getVel(),getVel())<.01){
			setVel(0,0,0);
		}
		translate(0,EASE_VAL*dir,0);
	}
	//DIFFERENCE - REQUIRES !midInZ
	//within the "z prism"
	if(midInX&&midInY&&!midInZ){
		if(midDist.y!=0)dir=midDist.y/abs(midDist.y);
		else dir=0;

		if(abs(d1.z)>b1.getDimensions().z/EASE_SCALE_VAL||abs(d2.z)>b1.getDimensions().z/EASE_SCALE_VAL)dir=0;

		if(abs(d1.z)<abs(d2.z)){
			if(getVel().z<0)
			{
				newPos.z=b2.getPoint1().z+b1.getDimensions().z/2;
			}
		}else{
			if(getVel().z>0)
			{
				newPos.z=b2.getPoint2().z-b1.getDimensions().z/2;
			}
		}
		
		if(newPos.z!=0){
			setTranslateZ(newPos.z);
			setVelZ(0);
		}
		translate(0,0,EASE_VAL*dir);
	}

	vec3 v=getTranslate()-newPos;
}