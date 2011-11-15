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
			currentCamera->setParent(pl);
			currentCamera->translate(0,2.5,5);

			DrawableEntity d=DrawableEntity(NULL,"Resources/test.obj");
			d.setDiffuseColor(1,0,0);
			d.setShininess(20);
			d.setAlpha(.5);

			std::cout<<"TEST Trans: "<<d.isAlphaRequired()<<std::endl;


			Globals::addEntity(pl);

			PointLight* p=new PointLight(vec3(1,1,1),0,1);
			p->translate(10,10,-10);
			p->setFalloff(0);
			p->setBrightness(1);
			addLight(p);

			p=new PointLight(vec3(1,1,0),1,1);
			p->translate(0,-12,0);
			addLight(p);

			Wall*  w=new Wall();
			w->scale(10,10,10);
			w->translate(0,-20,0);
			addWall(w);

			w=new Wall();
			w->scale(50,1,50);
			w->translate(0,-16,0);
			addWall(w);


			w=new Wall();
			w->scale(1,1,1);
			w->translate(0,0,10);
			w->setModel(d);
			//w->scale(.1,.1,.1);
			addWall(w);

		}
		void update(){
			//wWalls[2]->rotate(0,1,0);
		}
		bool levelEnd()const{
			return false;
		}
	};
}

#endif