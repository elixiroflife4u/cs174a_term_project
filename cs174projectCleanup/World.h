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

	const int WALL_COUNT=40;
	const int GAMEENTITY_COUNT=200;
	const int SCENE_COUNT=10;
	const int LIGHT_COUNT=10;
	const int BULLETS_COUNT=100;

	extern Wall* wWalls[WALL_COUNT]; //Wall Array
	extern GameEntity* wEntities[GAMEENTITY_COUNT]; //All other entities pointer (enemies etc)
	extern PointLight* wLights[LIGHT_COUNT];
	extern Scene* wScenes[SCENE_COUNT];//Array of Scenes
	typedef std::list<BulletEntity*> BulletList;
	extern BulletList wBullets;
	
	bool addWall(Wall* w);
	bool deleteWall(Wall* w);
	bool addEntity(GameEntity* g);
	bool deleteEntity(GameEntity* g);
	bool addLight(PointLight* pl);
	bool deleteLight(PointLight* pl);
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
	/** Deletes a bullet and removes it fromthe global list.
	  * This is the preferred way to delete a bullet since
	  * it is constant time.
	  * @return Iterator to the next bullet.
	  */
	BulletList::iterator delBullet(BulletList::iterator b);
	void deleteAllWorld();
	

	extern vec3 grav;

	extern int currentLevel;
	//pointer to the current camera
}

#include "Scene.h"

#endif //_WORLD