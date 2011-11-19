#ifndef _SCENE
#define _SCENE

#include "Engine.h"
#include "World.h"
#include "Player.h"
#include "Explosion.h"
#include "TurretEntity.h"

namespace Globals{

	class Scene{
	public:
		virtual void setup()=0;
		virtual void update()=0;
		virtual bool levelEnd()const=0;
		virtual void cleanup(){
		
		}
	};

	class Scene_1:public Scene{
	private:
		float _count;
	public:
		void setup(){
			Player* pl=new Player();
			currentCamera=pl->getCamera();
			pl->translate(0,2,0);

			Globals::addEntity(pl);

			PointLight* p=new PointLight(vec3(1,1,1),0,5);
			p->translate(10,10,-10);
			p->setFalloff(2);
			p->setBrightness(1);
			//addLight(p);

			p=new PointLight(vec3(1,1,1),1,15);
			p->translate(0,20,0);
			addLight(p);
			p=new PointLight(vec3(1,1,1),2,2);
			p->translate(-1,.1,0);
			p->setParent(pl);
			addLight(p);
			p=new PointLight(*p);
			p->translate(2,0,0);
			addLight(p);

			
			addEntity(new TurretEntity(vec3(0,6,0)));





			//large floor
			Wall* w=new Wall();
			w->scale(100,1,100);
			w->translate(0,0,0);
			addWall(w);

			w=new Wall();
			w->scale(500,4,25);
			w->translate(50,-3,25);
			addWall(w);
			
			//Beginning area
			//walls
			w=new Wall();
			w->scale(5,9,70);
			w->translate(-25,4.5,10);
			addWall(w);

			w=new Wall();
			w->scale(70,7.5,5);
			w->translate(10,4,-25);
			addWall(w);

			w=new Wall();
			w->scale(70,7.5,5);
			w->translate(10,4,35);
			addWall(w);

			
			//Flourishes
			w=new Wall();
			w->scale(6,20,8);
			w->translate(-20,10,20);
			addWall(w);

			w=new Wall();
			w->scale(9,10,8);
			w->translate(-19,5,15);
			addWall(w);

			w=new Wall();
			w->scale(10,1,10);
			w->translate(0,1,0);
			addWall(w);

			_count=0;
		}
		void update(){
			//wWalls[2]->rotate(0,1,0);
			_count+=M_PI/10;
			//wLights[0]->translate((sin(_count)),0,sin(_count));
			//std::cout<<sin(_count)<<std::endl;
		}
		bool levelEnd()const{
			return false;
		}
	};
}

#endif