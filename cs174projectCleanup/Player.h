#ifndef _PLAYER
#define _PLAYER


#include "MobileEntity.h"
#include "CameraEntity.h"
#include "Shield.h"
/** @brief This concrete class encapulates all player-specific behavior and
 *         appearances.
 */
class Player:public MobileEntity{
private:
	CameraEntity _playerCamera;
	int _livesCount;
	int _currentWeapon;

	int _shieldCharge;

	bool Q_PRESSED;
	bool E_PRESSED;

	int bulletDelay;

	int _shieldTime;

public:
	static const int MAX_HEALTH=100;
	static const int MAX_SHIELD=500;
	static const int MAX_DELAY=6;
	Player()
		:MobileEntity(ID_PLAYER),_livesCount(3),_currentWeapon(ID_BULLET_STRAIGHT),_shieldCharge(MAX_SHIELD),Q_PRESSED(false),E_PRESSED(false),_shieldTime(0)
	{
		setModel(DrawableEntity("resources/tankTexture.png","resources/tankBase.obj",this));
		getModel().scale(.5,.5,.5);
		//getModel().setDiffuseColor(.4,.4,.5);
		getModel().setShininess(50);
		setModel(DrawableEntity("resources/tankTexture.png","resources/tankTop.obj",this),1);
		getModel(1).translate(0,.65,.5);
		getModel(1).scale(.5,.5,.5);
		//getModel(1).setDiffuseColor(.4,.4,.5);
		getModel(1).setShininess(1000);

		getModel().setNormalMap("resources/floorNormal.jpg");
		getModel(1).setNormalMap("resources/floorNormal.jpg");

		getModel().setNormalMapDepth(0);
		getModel(1).setNormalMapDepth(0);

		CollisionBox b;
		b.scale(3,2.5,3);

		GameEntity::setHitbox(b);

		_playerCamera.setParent(&getModel(1));

		_playerCamera.translate(0,7,7);
		_playerCamera.rotate(-15,0,0);

		bulletDelay=0;
		//Globals::addSoftEntity(new Shield(getTranslate(), 10,40,this));
		
	}
	void update();
	void onCollide(const GameEntity& g);
	void onBulletCollision(float damage);
	float getShieldCharge()const {return _shieldCharge;}

	CameraEntity* const getCamera(){return &_playerCamera;}

	int getLivesNum(){return _livesCount;}
	void incWeapon(){_currentWeapon++;}
	void decWeapon(){_currentWeapon++;}
	int getWeapon()const {return _currentWeapon;}
};



#endif //_PLAYER