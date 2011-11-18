#include "World.h"
#include "GameEntity.h"
#include "StraightBulletEntity.h"
#include "GrenadeEntity.h"
#include "Explosion.h"
#include <algorithm>

namespace Globals
{
	//FOR OUR GAME//

	//transparent object heap

	GameEntityList wWalls;
	GameEntityList wEntities;
	GameEntityList wSoftEntities;
	PointLight* wLights[LIGHT_COUNT]; //pointer to lights inthe scene
	Scene* wScenes[SCENE_COUNT];//Array of Scenes

	bool addWall(Wall* w){
		//Adds a wall to the scene
		if(wWalls.size() == WALL_COUNT) return false;
		wWalls.push_back(w);
		return true;
	}
	GameEntityList::iterator deleteWall(GameEntityList::iterator w){
		//Removes a wall to the scene
		delete *w;
		return wWalls.erase(w);
	}

	bool addEntity(GameEntity* g){
		//Adds the passed GameEntity to the scene
		if(wEntities.size() == GAMEENTITY_COUNT) return false;
		wEntities.push_back(g);
		return true;
	}

	GameEntityList::iterator deleteEntity(GameEntityList::iterator g){
		//Removes a entities to the scene
		delete *g;
		return wEntities.erase(g);
	}

	bool addLight(PointLight* pl){
		//Adds the passed light to the scene
		//light should be dynamically allocated
		for(int i=0; i<LIGHT_COUNT;i++){
			if(wLights[i]==NULL){
				wLights[i]=pl;
				return true;
			}
		}
		return false;
	}
	bool deleteLight(PointLight* pl){
		//Removes a entities to the scene
		if(pl==NULL){
			return false;
		}

		for(int i=0; i<LIGHT_COUNT;i++){
			if(wLights[i]==pl){
				wLights[i]=NULL;
				delete pl;
				return true;
			}
		}
		return false;
	}

	bool addBullet(int bulletType, float accelMag, float initialVelMag, vec3 direction, 
		           vec3 startPosition, float damage, int numberOfAcclUpdates) {
		if(wSoftEntities.size() == SOFT_ENTITIES_COUNT) return false;
		switch(bulletType) {
		case ID_BULLET_STRAIGHT:
			wSoftEntities.push_back(new StraightBulletEntity(accelMag, initialVelMag, direction,
				                                        startPosition, damage, numberOfAcclUpdates));
			std::cerr<<"Soft entities alive: "<<wSoftEntities.size()<<'\n';
			break;
		case ID_BULLET_GRENADE:
			wSoftEntities.push_back(new GrenadeEntity(startPosition,direction));
			break;
		default:
			throw new CException("Unknown bullet type given to addBullet()");
			break;
		}
		return true;
	}
	GameEntityList::iterator deleteSoftEntity(GameEntityList::iterator b) {
		delete *b;
		std::cerr<<"Soft entities alive: "<<wSoftEntities.size() - 1<<'\n';
		return wSoftEntities.erase(b);
	}

	template<typename T>
	static inline void deleteAll(T& container) {
		for(T::iterator i = container.begin(); i != container.end(); ++i)
			delete *i;
	}

	void deleteAllWorld(){
		deleteAll(wWalls);
		deleteAll(wEntities);
		deleteAll(wSoftEntities);

		//delete every light and set it to null
		for(int i=0; i<LIGHT_COUNT;i++){
			if(wLights[i]!=NULL){
				delete wLights[i];
				wLights[i]=NULL;
			}
		}
	}


	vec3 grav=vec3(0,-.1,0);

	int currentLevel=0;
	//pointer to the current camera
}
