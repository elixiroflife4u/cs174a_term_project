#ifndef _WORLD
#define _WORLD

#include "Angel.h"
namespace Globals
{
	//ENGINE BASICS//
	extern GLuint sProgram;

	//Key States
	extern bool KEY_W;
	extern bool KEY_A;
	extern bool KEY_S;
	extern bool KEY_D;
	extern bool KEY_Q;
	extern bool KEY_E;
	extern bool KEY_SPACE;

	extern int mouseX;
	extern int mouseY;

	//set texture offset
	//set texture scale
	//set position of lights/amount of lights/color of lights/falloff of lights
	//set shininess
	//set transformation matrix
	//set camera position
	
	//FOR OUR GAME//
	//Include Bullets
	//Include Walls
	//Include MainChar
	//Include GameEntity

	//Array of Walls
	//Array of Bullets
	//Array of GameEntities
	//Array of Scenes
	//transparent object heap

	extern vec3 grav;

	extern int currentLevel;
	//pointer to the current camera
}

#endif //_WORLD