#ifndef _WORLD
#define _WORLD

#include "Angel.h"
#include "Wall.h"
#include "Player.h"
#include "GameEntity.h"


namespace Globals
{
	class Scene;
	
	//FOR OUR GAME//

	const int WALL_COUNT=40;
	const int GAMEENTITY_COUNT=200;
	const int SCENE_COUNT=10;
	const int LIGHT_COUNT=10;

	extern Wall* wWalls[WALL_COUNT]; //Wall Array
	extern GameEntity* wEntities[GAMEENTITY_COUNT]; //All other entities pointer (enemies etc)
	extern PointLight* wLights[LIGHT_COUNT];
	extern Scene* wScenes[SCENE_COUNT];//Array of Scenes
	
	bool addWall(Wall* w);
	bool addEntity(GameEntity* g);
	bool addLight(PointLight* pl);
	void deleteAllWorld();
	//transparent object heap

	extern vec3 grav;

	extern int currentLevel;
	//pointer to the current camera
}

#include "Scene.h"

#endif //_WORLD