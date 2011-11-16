#include "World.h"
#include "GameEntity.h"
#include "StraightBulletEntity.h"

namespace Globals
{
	//FOR OUR GAME//

	//transparent object heap

	Wall* wWalls[WALL_COUNT]; //Wall Array
	GameEntity* wEntities[GAMEENTITY_COUNT]; //All other entities pointer (enemies etc)
	PointLight* wLights[LIGHT_COUNT]; //pointer to lights inthe scene
	Scene* wScenes[SCENE_COUNT];//Array of Scenes
	BulletList wBullets;

	bool addWall(Wall* w){
		//Adds a wall to the scene
		//Wall should be dynamically allocated
		for(int i=0; i<WALL_COUNT;i++){
			if(wWalls[i]==NULL){
				wWalls[i]=w;
				return true;
			}
		}
		return false;
	}
	bool deleteWall(Wall* w){
		//Removes a wall to the scene
		if(w==NULL){
			return false;
		}

		for(int i=0; i<WALL_COUNT;i++){
			if(wWalls[i]==w){
				wWalls[i]=NULL;
				delete w;
				return true;
			}
		}
		return false;
	}

	bool addEntity(GameEntity* g){
		//Adds the passed GameEntity to the scene
		//GameEntity should be dynamically allocated
		for(int i=0; i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]==NULL){
				wEntities[i]=g;
				return true;
			}
		}
		return false;
	}

	bool deleteEntity(GameEntity* g){
		//Removes a entities to the scene
		if(g==NULL){
			return false;
		}

		for(int i=0; i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]==g){
				wEntities[i]=NULL;
				delete g;
				return true;
			}
		}
		return false;
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
		if(wBullets.size() == BULLETS_COUNT) return false;
		switch(bulletType) {
		case ID_BULLET_STRAIGHT:
			wBullets.push_back(new StraightBulletEntity(accelMag, initialVelMag, direction,
				                                        startPosition, damage, numberOfAcclUpdates));
			break;
		case ID_BULLET_BOUNCEGRENADE:
			throw new CException("Bounce grenade not implemented");
			break;
		default:
			throw new CException("Unknown bullet type given to addBullet()");
			break;
		}
		return true;
	}
	BulletList::iterator delBullet(BulletList::iterator b) {
		delete *b;
		return wBullets.erase(b);
	}

	void deleteAllWorld(){
		//delete every wall adn set it to null
		for(int i=0; i<WALL_COUNT;i++){
			if(wWalls[i]!=NULL){
				delete wEntities[i];
				wWalls[i]=NULL;
			}
		}
		//delete every entity and set it to null
		for(int i=0; i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]!=NULL){
				delete wEntities[i];
				wEntities[i]=NULL;
			}
		}
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
