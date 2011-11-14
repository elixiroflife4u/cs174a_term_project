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
void Player::onCollide(const GameEntity& g){
	///@todo implement
	// collision detection for walls - so that the player can "land" on them and run into them
	// perhaps abstract it to the Mobileentity level because other mobile entities will need hit detection for walls as well

}