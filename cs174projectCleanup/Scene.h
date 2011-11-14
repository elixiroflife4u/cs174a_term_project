#ifndef _SCENE
#define _SCENE

#include "Engine.h"
#include "World.h"
#include "Player.h"


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

	public:
		void setup(){
			Player* pl=new Player();
			camera.setParent(pl);
			

			Globals::addEntity(pl);



			PointLight* p=new PointLight(vec3(1,1,1),0,1);
			p->translate(10,10,-10);
		//	p->setFalloff(3);
		//	p->setBrightness(50);
			addLight(p);


		}
		void update(){
		}
		bool levelEnd()const{
			return false;
		}
	};
}

#endif