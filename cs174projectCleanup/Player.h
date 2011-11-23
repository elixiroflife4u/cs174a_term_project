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
	static const int MAX_SHIELD=400;
	static const int MAX_DELAY=6;

	/** @brief initializes the player entity
	*/
	Player()
		:MobileEntity(ID_PLAYER),_livesCount(3),_currentWeapon(ID_BULLET_STRAIGHT),_shieldCharge(MAX_SHIELD),Q_PRESSED(false),E_PRESSED(false),_shieldTime(0)
	{
		//creates the models and sets the parameters for them
		setModel(DrawableEntity("resources/tankTexture.png","resources/tankBase.obj",this));
		getModel().scale(.5,.5,.5);
		getModel().setShininess(50);

		setModel(DrawableEntity("resources/tankTexture.png","resources/tankTop.obj",this),1);
		getModel(1).translate(0,.65,.5);
		getModel(1).scale(.5,.5,.5);
		getModel(1).setShininess(1000);

		getModel().setNormalMap("resources/floorNormal.jpg");
		getModel(1).setNormalMap("resources/floorNormal.jpg");

		getModel().setNormalMapDepth(0);
		getModel(1).setNormalMapDepth(0);

		//Create a new hitbox for the player entity
		CollisionBox b;
		b.scale(3,2.5,3);

		GameEntity::setHitbox(b);

		//initialize the camera to a resonable location
		_playerCamera.setParent(&getModel(1));

		_playerCamera.translate(0,7,7);
		_playerCamera.rotate(-15,0,0);

		bulletDelay=0;
	}
	/** @brief Updates the player's position and shoots
	* based off of key presses
	*/
	void update();

	/** @brief if the player collides with a wall, then it is placed at the
	* edge. If it collides with a bullet, damage is applied
	*/
	void onCollide(const GameEntity& g);
	void onBulletCollision(float damage);
	
	/** @brief returns the total recharge remaining for the shield
	* -- used for the UI
	*/
	float getShieldCharge()const {return _shieldCharge;}

	/** @brief returns the camera attached to the player
	*/
	CameraEntity* const getCamera(){return &_playerCamera;}

	int getLivesNum(){return _livesCount;}

	/* @brief Increases or decreases the weapons number being used */
	void incWeapon(){_currentWeapon++;}
	void decWeapon(){_currentWeapon++;}

	/** @brief Returns the current weapon being used
	* used for the UI
	*/
	int getWeapon()const {return _currentWeapon;}
};



#endif //_PLAYER