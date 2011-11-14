#ifndef _WALL
#define _WALL

#include "GameEntity.h"

class Wall:public GameEntity{
private:
public:
	Wall()
		:GameEntity(ID_WALL)
	{
		setModel(DrawableEntity(NULL,"Resources/cube.obj"));
		scale(10,10,10);
		translate(0,0,-8);
		//rotate(0,45,0);
		//getModel(0)->setShininess(100);

		std::cout<<getModel(0)->getTransformationMatrix()[1][3]<<std::endl;
		std::cout<<getTranslate().y<<std::endl;
	}
	void update(){}
};

#endif //_WALL