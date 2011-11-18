#ifndef _WALL
#define _WALL

#include "GameEntity.h"

class Wall:public GameEntity{
private:
public:
	Wall()
		:GameEntity(ID_WALL)
	{
		setModel(DrawableEntity("Resources/decal.bmp","Resources/cube.obj"));
		//getModel().setDiffuseColor(.5,.5,.5);
		getModel().setUVScale(10,10);
	}
	void update(){}
	void onCollide(const GameEntity&){}
};

#endif //_WALL