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
	}
	void update(){}
	void onCollide(const GameEntity&){}
};

#endif //_WALL