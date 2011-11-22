#ifndef _SCENE
#define _SCENE

#include "Engine.h"
#include "World.h"
#include "Player.h"
#include "Explosion.h"
#include "TurretEntity.h"
#include "WanderingEnemy.h"

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
		CollisionBox c;
		Wall* room1Door;

		bool room1Trigger;
		bool bossTrigger;

		WanderingEnemy* e[10];

	public:
		void setup(){
			Player* pl=new Player();
			currentCamera=pl->getCamera();
			pl->translate(0,5,0);
			//pl->translate(125,0,330);
			pl->rotate(0,-90,0);


			Globals::addEntity(pl);

			PointLight* p=new PointLight(vec3(1,1,1),0,5);
			p->translate(10,10,-10);
			p->setFalloff(2);
			p->setBrightness(1);
			//addLight(p);

			p=new PointLight(vec3(1,1,1),1,15);
			p->translate(0,20,0);
			addLight(p);

			p=new PointLight(vec3(1,1,1),1,15);
			p->translate(80,20,0);
			addLight(p);


			p=new PointLight(vec3(1,1,1),2,2);
			p->translate(-1,.1,0);
			p->setParent(pl);
			addLight(p);
			p=new PointLight(*p);
			p->translate(2,0,0);
			addLight(p);

			
			//addEntity(new TurretEntity(vec3(10,3.5,10)));
			//addEntity(new TurretEntity(vec3(-10,3.5,10)));
			//addEntity(new TurretEntity(vec3(0,3.5,10)));
			addEntity(new TurretEntity(vec3(50,3.5,45)));
			addEntity(new TurretEntity(vec3(50,3.5,55)));

			addEntity(new TurretEntity(vec3(95,3.5,45)));
			addEntity(new TurretEntity(vec3(95,3.5,55)));

			addEntity(new TurretEntity(vec3(150-85,5,330-50)));
			addEntity(new TurretEntity(vec3(150-85,5,330+60)));

			addEntity(new TurretEntity(vec3(150+40,5,330-50)));
			addEntity(new TurretEntity(vec3(150+40,5,330+60)));

			TurretEntity* t=new TurretEntity(vec3(175,20,330));
			t->scale(5,5,5);
			t->rotate(0,-90,0);
			addEntity(t);

			//large floor
			//Grass
			DrawableEntity grass=DrawableEntity("resources/grassTexture.jpg","Resources/cube.obj");
			grass.setNormalMap("Resources/floorNormal.jpg");
			//grass.setDiffuseColor(.4,.75,.4);
			grass.setUVScale(55,55);
			grass.setShininess(500);
			Wall* w=new Wall();
			w->setModel(grass);
			w->scale(175,1,175);
			w->translate(50,0,0);
			addWall(w);

			w=new Wall();
			w->scale(40,4,200);
			w->translate(80,1,175);
			addWall(w);

			w=new Wall();
			w->scale(150,3,150);
			w->translate(125,0,330);
			addWall(w);

			w=new Wall();
			w->scale(20,10,15);
			w->translate(125, 5, 332.5+65);
		//	addWall(w);

			//Beginning area
			//walls
			//back
			w=new Wall();
			w->scale(5,9,70);
			w->translate(-25,4.5,10);
			addWall(w);

			w=new Wall();
			w->scale(5,8,150);
			w->translate(100,4,10);
			addWall(w);

			//left
			w=new Wall();
			w->scale(130,7.5,5);
			w->translate(35,4,-25);
			addWall(w);
			//right
			w=new Wall();
			w->scale(80,7.5,5);
			w->translate(10,4,35);
			addWall(w);
			
			//first hall
			//left
			w=new Wall();
			w->scale(6,30,200);
			w->translate(95,15,175);
			addWall(w);
			//right
			w=new Wall();
			w->scale(6,30,200);
			w->translate(60,15,175);
			addWall(w);
			
			w=new Wall();
			w->scale(40,15,200);
			w->translate(78,35,175);
			addWall(w);

			p=new PointLight(vec3(1,1,1),2,60);;
			p->setTranslate(75,20,115);
			addLight(p);
			p=new PointLight(*p);
			p->translate(0,0,40);
			addLight(p);
			p=new PointLight(*p);
			p->translate(0,0,40);
			addLight(p);


			//first Fight Room
			//left and right walls
			w=new Wall();
			w->scale(3,100,150);
			w->translate(125-68,50,330);
			addWall(w);
			w=new Wall();
			w->scale(3,100,150);
			w->translate(125+75,50,330);
			addWall(w);

			//back
			w=new Wall();
			w->scale(120,100,3);
			w->translate(125+30,50,330-75);
			addWall(w);
			w=new Wall();
			w->scale(50,70,3);
			w->translate(125-55,65,330-75);
			addWall(w);

			//front
			w=new Wall();
			w->scale(200,100,8);
			w->translate(125,50,330+75);
			addWall(w);

			room1Door=w=new Wall();
			w->scale(40,50,8);
			w->translate(80,50,250);
			addWall(w);

			//cieling
			w=new Wall();
			w->scale(150,3,150);
			w->translate(125,100,330);
			addWall(w);

			p=new PointLight(vec3(1,1,1), 1, 40);
			p->translate(125,75,330);
			addLight(p);


			//Flourishes
			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->translate(-20,10,20);
			DrawableEntity d1=DrawableEntity(NULL,"Resources/rockTall.obj");
			d1.setDiffuseColor(.5,.5,.5);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->rotate(0,270,0);
			w->translate(-20,3,33);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->translate(100,10,20);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->translate(95,5,15);
			w->scale(.5,.5,.5);
			w->rotate(0,-90,0);
			w->setModel(d1);
			addWall(w);


			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,14)));
			w->translate(10,10,30);
			w->scale(1.5,1.5,1.5);
			w->rotate(15,180,0);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,14)));
			w->translate(55,10,70);
			w->scale(1.5,1.5,1.5);
			w->rotate(15,180,0);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->translate(90,5,70);
			w->scale(1,1,1);
			w->rotate(0,90,0);
			w->setModel(d1);
			addWall(w);


			d1=DrawableEntity(NULL,"Resources/rockMed.obj");
			d1.setDiffuseColor(.25,.25,.25);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(9,30,8)));
			w->setModel(d1);
			w->translate(-19,5,-2);
			w->rotate(0,90,0);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(9,30,8)));
			w->setModel(d1);
			w->translate(50,5,35);
			w->rotate(0,90,0);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(9,30,8)));
			w->setModel(d1);
			w->translate(45,5,75);
			w->rotate(0,-90,0);
			w->scale(2,2,2);
			addWall(w);

			d1=DrawableEntity(NULL,"Resources/rockFlat.obj");
			d1.setDiffuseColor(.5,.5,.5);

			w=new Wall();
		//	w->scale(10,1,10);
			w->setHitbox(CollisionBox(vec3(10,2,10)));
			w->setModel(d1);
			w->translate(0,1,0);
			addWall(w);

			addEntity(new WanderingEnemy(vec3(-10,9,0)));

			//Trees

			DrawableEntity d= DrawableEntity("Resources/treesTest.png","Resources/plane.obj");
			d.setHighlightColor(.1,.05,.1);
			d.rotate(-90,0,0);
			d.setAlphaRequired(true);
			d.setUVScale(1,-1);

			for(int i=0;i<2;i++){
				d.setRotate(-90,0,0);

				w=new Wall();
				w->setModel(d);
				w->translate(30-40*i,25,40);
				w->scale(50,50,2);
				addWall(w);

				w=new Wall();
				d.scale(1,-1,1);
				w->setModel(d);
				w->translate(30-40*i,25,-40);
				w->scale(50,50,2);
				addWall(w);
			
				w=new Wall();
				d.scale(1,-1,1);
				w->setModel(d);
				w->translate(110-40*i,25,-40);
				w->scale(50,50,2);
				addWall(w);

				w=new Wall();
				d.setRotate(-90,0,90);
				w->setModel(d);
				w->translate(-30,25,-20+40*i);
				w->scale(2,50,50);
				addWall(w);

				w=new Wall();
				d.setRotate(-90,0,90);
				w->setModel(d);
				w->translate(115,25,-20+40*i);
				w->scale(2,50,50);
				addWall(w);
		
				w=new Wall();
				d.setRotate(-90,0,90);
				w->setModel(d);
				w->translate(115,25,60+40*i);
				w->scale(2,50,50);
				addWall(w);

				w=new Wall();
				d.setRotate(-90,0,90);
				w->setModel(d);
				w->translate(40,25,60-120*i);
				w->scale(2,50,50);
				addWall(w);

			}

			d.setRotate(-90,0,0);
			w=new Wall();
			d.scale(1,-1,1);
			w->setModel(d);
			w->translate(40,25,80);
			w->scale(50,50,2);
			addWall(w);
			_count=0;

			c.scale(200,100,75);
			c.translate(150,50,330);

			room1Trigger=false;
			bossTrigger=false;

			for(int i=0;i<10;i++){
				e[i]=new WanderingEnemy(vec3(100+5*i,50,330));
				//addEntity(e[i]);
			}
		}
		void update(){
			//wWalls[2]->rotate(0,1,0);
			_count+=M_PI/10;
			//wLights[0]->translate((sin(_count)),0,sin(_count));
			//std::cout<<sin(_count)<<std::endl;

			if(c.didCollide(getPlayer()->getHitBox())&&!room1Trigger){
				room1Trigger=true;
				for(int i=0;i<5;i++){
					addEntity(e[i]);
				}
			}else if(room1Trigger&&room1Door->getTranslate().y>25){
				room1Door->translate(0,-2,0);
			}


			if(dot(getPlayer()->getTranslate(),getPlayer()->getTranslate())<pow(20.0,2)&&room1Trigger){
				getPlayerGE()->setTranslate(125,10,330);

			}


		}
		bool levelEnd()const{
			return false;
		}
	};
}

#endif