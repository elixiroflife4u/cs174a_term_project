#include "Player.h"
#include "Engine.h"
#include "World.h"

#include <iostream>
void Player::update()
{
	///@todo implement

	increaseVel(Globals::grav);
	
	translate(getVel());
	std::cout<<getTranslate().y<<std::endl;
}