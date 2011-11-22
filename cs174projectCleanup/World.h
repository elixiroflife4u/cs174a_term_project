#ifndef _WORLD
#define _WORLD

#include "Angel.h"
#include "Wall.h"
#include "Player.h"
#include "GameEntity.h"

#include <list>

class BulletEntity;

namespace Globals
{
	class Scene;
	
	//FOR OUR GAME//
	extern bool firstPerson;


	const int WALL_COUNT=100;
	const int GAMEENTITY_COUNT=200;
	const int SCENE_COUNT=10;
	const int LIGHT_COUNT=10;
	const int SOFT_ENTITIES_COUNT=100;

	extern GameEntity* wPlayer;
	typedef std::list<GameEntity*> GameEntityList;
	extern GameEntityList wEntities;
	extern GameEntityList wWalls;
	extern GameEntityList wSoftEntities;

	extern PointLight* wLights[LIGHT_COUNT];
	extern Scene* wScenes[SCENE_COUNT];//Array of Scenes
	
	bool addWall(Wall* w);
	GameEntityList::iterator deleteWall(GameEntityList::iterator w);
	bool addEntity(GameEntity* g);
	GameEntityList::iterator deleteEntity(GameEntityList::iterator g);
	bool addLight(PointLight* pl);
	bool deleteLight(PointLight* pl);

	const Player* const getPlayer();
	GameEntity* getPlayerGE();
	/** Attempts to construct a new bullet and add it to the world.
	  * @param bulletType The type of bullet as defined in GameEntityType.
	  * @param accelMag Magnitude of the acceleration vector.
	  * @param initialVelMag Initial magnitude of the velocity vector.
	  * @param direction Direction of bullet travel.
	  * @param startPosition Initial position.
	  * @param damage Damage factor.
	  * @param numberOfAcclUpdates Number of frames until accleration is reset to 0.
	  * @return False if too many bullets in the world already.
	  */
	bool addBullet(int bulletType, float accelMag, float initialVelMag, vec3 direction, 
		           vec3 startPosition, float damage=1, int numberOfAcclUpdates=5);
	bool addSoftEntity(GameEntity* g);
	/** Deletes a soft entity and removes it from the global list.
	  * This is the preferred way to delete a soft entity since
	  * it is constant time.
	  * @return Iterator to the next soft entity.
	  */
	GameEntityList::iterator deleteSoftEntity(GameEntityList::iterator b);
	void deleteAllWorld();
	

	extern vec3 grav;

	extern int currentLevel;
	//pointer to the current camera
}

#include "Scene.h"

#endif //_WORLD