#ifndef _WALL
#define _WALL

#include "GameEntity.h"

class Wall:public GameEntity{
private:
public:
	Wall()
		:GameEntity(ID_WALL)
	{
		setModel(DrawableEntity("Resources/mechTexture.png","Resources/cube.obj"));
		getModel().rotate(0,-90,0);
		//getModel().setDiffuseColor(.5,.5,.6);
		getModel().setUVScale(20,20);
		getModel().setNormalMap("Resources/mechNormal2.jpg");
		getModel().setNormalMapDepth(1);
		getModel().setShininess(5000);
	//	getModel().setDiffuseColor(1,0,0);
	}
	void update(){}
	void onCollide(const GameEntity&){}
};

#endif //_WALL