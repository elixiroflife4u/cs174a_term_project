#ifndef _PLAYER
#define _PLAYER

#include "MobileEntity.h"

/** @brief This concrete class encapulates all player-specific behavior and
 *         appearances.
 */
class Player:public MobileEntity{
private:
public:
	Player()
		:MobileEntity(ID_PLAYER)
	{
		GameEntity::setModel(DrawableEntity(NULL,"Resources/cube.obj",this));
	}
	void update();
};



#endif //_PLAYER