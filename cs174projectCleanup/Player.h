#ifndef _PLAYER
#define _PLAYER

#include "MobileEntity.h"
#include "CameraEntity.h"

/** @brief This concrete class encapulates all player-specific behavior and
 *         appearances.
 */
class Player:public MobileEntity{
private:
	CameraEntity _playerCamera;
	int _livesCount;
	int _currentWeapon;
public:
	
	Player()
		:MobileEntity(ID_PLAYER),_livesCount(3)
	{
		setModel(DrawableEntity(NULL,"Resources/tankBase.obj",this));
		getModel().scale(1,1,1);
		getModel().setDiffuseColor(.4,.4,.5);
		getModel().setShininess(50);
		setModel(DrawableEntity(NULL,"Resources/tankTop.obj",this),1);
		getModel(1).translate(0,.65,.5);
		getModel(1).scale(1,1,1);
		getModel(1).setDiffuseColor(.4,.4,.5);
		getModel(1).setShininess(50);

		CollisionBox b;
		b.scale(1.5,2.5,1.5);

		GameEntity::setHitbox(b);

		_playerCamera.setParent(&getModel(1));

		_playerCamera.translate(0,7,7);
		_playerCamera.rotate(-15,0,0);
	}
	void update();
	void onCollide(const GameEntity& g);
	void onBulletCollision(float damage);

	CameraEntity* const getCamera(){return &_playerCamera;}

	int getLivesNum(){return _livesCount;}
};



#endif //_PLAYER