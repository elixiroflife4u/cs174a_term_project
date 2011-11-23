#ifndef _WALL
#define _WALL

#include "GameEntity.h"

/** @brief A Wall is what is used to block the player
  * from falling off of the world. They make up the ground
  * and rocks around the player and also stop bullets
  * from passing through
  *
  */

class Wall:public GameEntity{
private:
public:
	Wall()
		:GameEntity(ID_WALL)
	{
		setModel(DrawableEntity("Resources/mechTexture.png","Resources/cube.obj"));
		getModel().rotate(0,-90,0);
		getModel().setUVScale(20,20);
		getModel().setNormalMap("Resources/mechNormal2.jpg");
		getModel().setNormalMapDepth(1);
		getModel().setShininess(5000);
	}
	void update(){}
	void onCollide(const GameEntity&){}
};

#endif //_WALL