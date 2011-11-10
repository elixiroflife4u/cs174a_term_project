#ifndef _PLAYER
#define _PLAYER

#include "MobileEntity.h"

/** @brief This concrete class encapulates all player-specific behavior and
 *         appearances.
 */
class Player:public MobileEntity{
private:
public:
	void update();
};



#endif //_PLAYER