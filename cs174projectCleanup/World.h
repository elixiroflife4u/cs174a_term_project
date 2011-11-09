#ifndef _WORLD
#define _WORLD

#include "Angel.h"

//ENGINE BASICS//
GLuint sProgram=-1;

//Key States
bool KEY_W=false;
bool KEY_A=false;
bool KEY_S=false;
bool KEY_D=false;
bool KEY_Q=false;
bool KEY_E=false;
bool KEY_SPACE=false;

int mouseX=0;
int mouseY=0;

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

vec3 grav;

int currentLevel=0;
//pointer to the current camera





#endif //_WORLD