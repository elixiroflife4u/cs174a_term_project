#include "Player.h"
#include "Engine.h"
#include "World.h"
#include "BulletEntity.h"

#include <iostream>
void Player::update()
{
	///@todo implement

	const float MAX_VEL=1;
	const float ACCEL_AMOUNT=.15;

	/* should be moved */
	int xDelta=Globals::mouseX-glutGet(GLUT_WINDOW_WIDTH)/2;
	int yDelta=Globals::mouseY-glutGet(GLUT_WINDOW_HEIGHT)/2;

	glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2,glutGet(GLUT_WINDOW_HEIGHT)/2);

	rotate(0,-xDelta/10,0);
	//rotate(-yDelta/10,0,0);

	getModel(1).rotate(-yDelta/10,0,0);

	if(getModel(1).getRotate().x<0){
		getModel(1).setRotate(0,0,0);
	}else if(getModel(1).getRotate().x>45){
		getModel(1).setRotate(45,0,0);
	}

	increaseVel(Globals::grav);

	setAcc(0,0,0);
	//Calculate the acceleration vector depending on user input,
	//remembering to rotate it according to the player's local
	//rotation transformation. For now, I only consider the player's
	//rotation on the XZ-(horiontal)plane/Y-axis since it seems more
	//natural to me.
	vec4 localAccel;
	//if(Globals::KEY_Q) localAccel  = vec4(0,-ACCEL_AMOUNT,0,0);
	//if(Globals::KEY_E) localAccel += vec4(0,ACCEL_AMOUNT,0,0);
	if(Globals::KEY_W) localAccel += vec4(0,0,-ACCEL_AMOUNT,0);
	if(Globals::KEY_S) localAccel += vec4(0,0,ACCEL_AMOUNT,0);
	if(Globals::KEY_D) localAccel += vec4(ACCEL_AMOUNT,0,0,0);
	if(Globals::KEY_A) localAccel += vec4(-ACCEL_AMOUNT,0,0,0);
	if(Globals::KEY_SPACE) jump();
	const vec3 rotation = getLocalRotate();
	const vec4 rotatedAccel = RotateY(rotation.y) * localAccel;

	//The below cast might look dangerous, but it is essentially the same
	//(and _exactly_ as risky and C++-compliant) as what Angel does in
	//vec2/3/4's operator[]. If it's good enough for the textbook's author,
	//it's good enough for me.
	setAcc(*reinterpret_cast<const vec3*>(&rotatedAccel));
	increaseVel(*reinterpret_cast<const vec3*>(&rotatedAccel));

	vec3 horizVel=getVel();
	horizVel.y=0;

	if(dot(horizVel,horizVel)>pow(MAX_VEL,2)){
		horizVel=normalize(horizVel)*MAX_VEL;
		setVelX(horizVel.x);
		setVelZ(horizVel.z);
	}
	translate(getVel());

	if(Globals::MOUSE_EDGE_LEFT) {
		///@todo Find good values for these constants. Remember to offset the starting location
		/// so that it doesn't instantly collide with its creator.
		vec4 dir=(getModel(1).getTransformationMatrix()*vec4(0,0,-1,0));

		Globals::addBullet(ID_BULLET_GRENADE, 0, 4, vec3(dir.x,dir.y,dir.z), getModel(1).getTranslate(), 0, 10);
		//Globals::a
	}
}

void Player::onCollide(const GameEntity& g){
	switch(g.getId()) {
	case ID_WALL:
	case ID_ENEMY_TURRET:
		MobileEntity::placeAtEdge(g);
		break;
	case ID_BULLET_STRAIGHT:
	case ID_BULLET_GRENADE:
		onBulletCollision(static_cast<const BulletEntity*>(&g)->getBulletDamage());
		break;
	}
}

void Player::onBulletCollision(float damage) {
	///@todo implement
}
