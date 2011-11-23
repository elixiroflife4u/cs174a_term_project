#include "Player.h"
#include "Engine.h"
#include "World.h"
#include "BulletEntity.h"
#include "Shield.h"
#include "SoundPlayer.h"
#include <iostream>
void Player::update()
{
	if(getTranslate().y<-50)setHealth(0);

	if(getHealth()<=0){
		SoundPlayer::playSound("resources/death.wav", 1);
		Explosion* e = new Explosion(6,20);
		e->translate(getTranslate());
		Globals::addSoftEntity(e);

		setTranslate(0,10,0);
		setHealth(MAX_HEALTH);
		return;
	}

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
	if(Globals::KEY_Q) Q_PRESSED=true;
	if(Globals::KEY_E) E_PRESSED=true;

	if(!Globals::KEY_Q && Q_PRESSED){
		_currentWeapon--;
		Q_PRESSED=false;
	}
	if(!Globals::KEY_E && E_PRESSED){
		_currentWeapon++;
		E_PRESSED=false;
	}
	if(_currentWeapon==-1)_currentWeapon=2;
	_currentWeapon=_currentWeapon%3;

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

	//if(Globals::MOUSE_EDGE_LEFT) {
		///@todo Find good values for these constants. Remember to offset the starting location
		/// so that it doesn't instantly collide with its creator.
		vec4 dir=normalize((getModel(1).getTransformationMatrix()*vec4(0,0,-1,0)));
		vec4 dirR=normalize((getModel(1).getTransformationMatrix()*vec4(-1,0,0,0)));


		if(bulletDelay>0)bulletDelay--;

		switch(_currentWeapon){
		case 0: //straight
			if(!Globals::MOUSE_LEFT||bulletDelay!=0)break;
			Globals::addBullet(ID_BULLET_STRAIGHT, 0, 4, vec3(dir.x,dir.y,dir.z), getModel(1).getTranslate()-vec3(dirR.x,dirR.y,dirR.z)*.6+1*vec3(dir.x,dir.y,dir.z), 2, 10);
			Globals::addBullet(ID_BULLET_STRAIGHT, 0, 4, vec3(dir.x,dir.y,dir.z), getModel(1).getTranslate()+vec3(dirR.x,dirR.y,dirR.z)*.6+1*vec3(dir.x,dir.y,dir.z), 2, 10);
			SoundPlayer::playSound("resources/fireball.wav",1);
			bulletDelay=MAX_DELAY;
			break;
		case 1: //grenade
			if(!Globals::MOUSE_LEFT||bulletDelay!=0)break;
			Globals::addBullet(ID_BULLET_GRENADE, 0, 2.5, vec3(dir.x,dir.y,dir.z), getModel(1).getTranslate()+vec3(dir.x,dir.y,dir.z)*3.5, 0, 5);
			SoundPlayer::playSound("resources/cannon.wav",1);
			bulletDelay=MAX_DELAY*2;
			break;
		case 2: //other?
			if(!Globals::MOUSE_LEFT||bulletDelay!=0)break;
			SoundPlayer::playSound("resources/curvy.wav",1);
			Globals::addBullet(ID_BULLET_CURVY  , 0, 2.5, vec3(dir.x,dir.y,dir.z), getModel(1).getTranslate()+vec3(dir.x,dir.y,dir.z)*2, 0, 0);
			Globals::addBullet(ID_BULLET_CURVY  , 0, 2.5, vec3(dir.x,dir.y,dir.z), getModel(1).getTranslate()+vec3(dir.x,dir.y,dir.z)*3, 0, 0);
			bulletDelay=MAX_DELAY;
			break;
		}
	//}

	//SHIELDING
	if(Globals::MOUSE_EDGE_RIGHT){
		if(_shieldCharge>=MAX_SHIELD){
			Globals::addEntity(new Shield(getTranslate(),3,100,this));
			_shieldCharge=0;
			_shieldTime=90;
		}
	}
	if(_shieldTime>0)_shieldTime--;
	if(_shieldCharge<MAX_SHIELD)_shieldCharge++;

	float damageRatio=(MAX_HEALTH/2-getHealth())/MAX_HEALTH*5;
	if(damageRatio<0)damageRatio=0;
	getModel().setNormalMapDepth(damageRatio);
	getModel(1).setNormalMapDepth(damageRatio);


	//swap first person/third person view
	if(Globals::firstPerson){
		_playerCamera.setTranslate(0,3,1);
	}else{
		_playerCamera.setTranslate(0,7,7);
	}

	resetHightlight();
}

void Player::onCollide(const GameEntity& g){
	

	switch(g.getId()) {
	case ID_WALL:
	case ID_ENEMY_TURRET:
	case ID_WANDERING_EMEMY:
		MobileEntity::placeAtEdge(g);
		break;
	case ID_BULLET_STRAIGHT:
		onBulletCollision(3);
	case ID_BULLET_GRENADE:
	case ID_BULLET_CURVY:
		onBulletCollision(static_cast<const BulletEntity*>(&g)->getBulletDamage());
		break;
	}
}

void Player::onBulletCollision(float damage) {
	if(_shieldTime>0)return;
	decHealth(damage);

}
