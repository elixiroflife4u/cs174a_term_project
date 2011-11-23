#ifndef _SCENE
#define _SCENE

#include "Engine.h"
#include "World.h"
#include "Player.h"
#include "Explosion.h"
#include "TurretEntity.h"
#include "WanderingEnemy.h"
#include "TVScreen.h"

namespace Globals{

	class Scene{
		/** @brief A scene is basically a level
		* that is updated every frame along with the gameentities
		* so that level specifica interaction can take place
		*/

	public:
		bool _beaten;
		/** @brief The setup for the level should be done here (adding the walls and entities)*/
		virtual void setup()=0;
		/** @brief the interaction and animation of the level should be done here (triggers etc) */
		virtual void update()=0;
		/** @brief this is a win condition check for the level to see if the level has been beaten*/
		virtual bool levelEnd()const=0;
		/** @brief this is where any values that won't deleted by the world should be deleted/cleaned up*/
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

		TurretEntity* boss;

	public:
		/** @brief The entire level is set up and prepared here */
		void setup(){
			_beaten=false;
			//Add the player to the world
			Player* pl=new Player();
			currentCamera=pl->getCamera();
			pl->translate(0,5,0);
			pl->rotate(0,-90,0);			
			Globals::addEntity(pl);

			//Add some lights
			PointLight* p=new PointLight(vec3(1,1,1),1,15);
			p->translate(0,20,0);
			addLight(p);

			p=new PointLight(vec3(1,1,1),1,15);
			p->translate(80,20,0);
			addLight(p);


			p=new PointLight(vec3(.5,1,.7),2,3);
			p->translate(0,.1,.6);
			p->setParent(pl);
			addLight(p);
			p=new PointLight(*p);
			p->translate(2,0,0);
			//addLight(p);

			
			//addEntity(new TurretEntity(vec3(10,3.5,10)));
			//addEntity(new TurretEntity(vec3(-10,3.5,10)));
			//addEntity(new TurretEntity(vec3(0,3.5,10)));
			addEntity(new TurretEntity(vec3(50,3.5,45)));
			//addEntity(new TurretEntity(vec3(50,3.5,55)));

			addEntity(new TurretEntity(vec3(95,3.5,45)));
			//addEntity(new TurretEntity(vec3(95,3.5,55)));

			addEntity(new TurretEntity(vec3(150-85,5,330-50)));
			addEntity(new TurretEntity(vec3(150-85,5,330+60)));

			//addEntity(new TurretEntity(vec3(150+40,5,330-50)));
			//addEntity(new TurretEntity(vec3(150+40,5,330+60)));

			TurretEntity* boss=new TurretEntity(vec3(175,13,330));
			boss->scale(4,4,4);
			boss->rotate(0,-90,0);
			boss->setBoss(true);
			addEntity(boss);

			//large floor
			//Grass
			DrawableEntity floor=DrawableEntity("resources/grassTexture.jpg","Resources/cube.obj");
			floor.setNormalMap("Resources/floorNormal.jpg");
			//grass.setDiffuseColor(.4,.75,.4);
			floor.setUVScale(45,45);
			floor.setShininess(500);
			Wall* w=new Wall();
			w->setModel(floor);
			w->scale(175,1,175);
			w->translate(50,0,0);
			addWall(w);

			//diamondplat
			floor=DrawableEntity(NULL,"resources/cube.obj");
			floor.setNormalMap("resources/diamondPlateNormal.jpg");
			floor.setUVScale(20,80);
			floor.setShininess(1000);
			floor.setNormalMapDepth(1);
			floor.setDiffuseColor(.25,.25,.25);

			w=new Wall();
			w->setModel(floor);
			w->scale(40,4,200);
			w->translate(78,1,175.5);
			addWall(w);

			w=new Wall();
			w->scale(150,3,150);
			w->translate(125,0,330);
			addWall(w);

			//Beginning area
			//walls
			//back
			w=new Wall();
			w->scale(5,9,70);
			w->translate(-25,4.5,10);
			addWall(w);

			w=new Wall();
			w->scale(5,8,120);
			w->translate(100,4,30);
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
			DrawableEntity dWall=DrawableEntity("Resources/mechTexture.png","resources/wall.obj");
			dWall.setNormalMap("Resources/mechNormal2.jpg");
			dWall.setShininess(5000);
			dWall.setScale(1,1,.27);
			dWall.setUVScale(2,2);

			w=new Wall();
			w->scale(6,25,193);
			w->translate(95,15,175);
			
			Wall* wRight=new Wall();
			wRight->scale(6,25,193);
			wRight->translate(60,15,175);

			for(int i=0;i<4;i++){
				dWall.setTranslate(0,0,-.1225-.25+.25*i);

				w->setModel(dWall,i);
				wRight->setModel(dWall,i);
			
			}
			addWall(w);
			addWall(wRight);

			dWall.setUVScale(25,2);
			dWall.setScale(1,1,1);
			dWall.setTranslate(0,0,0);
			dWall.setDiffuseColor(.25,.25,.25);

			w=new Wall();
			w->scale(40,15,200);
			w->translate(78,35,175);
			w->setModel(dWall);
			addWall(w);


			p=new PointLight(vec3(1,1,1),2,60);;
			p->setTranslate(77.,20,115);
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
			w->scale(6,100,150);
			w->translate(125-71.5,50,330);
			addWall(w);
			w=new Wall();
			w->scale(9,100,150);
			w->translate(125+72,50,330);
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

			DrawableEntity warningDoor=DrawableEntity("resources/ClosedDoorTex.png","resources/wall.obj");
			warningDoor.setNormalMap("resources/mechNormal2.jpg");
			warningDoor.setNormalMapDepth(.5);
		//	warningDoor.setShininess(100);
			room1Door=w=new Wall();
			room1Door->setModel(warningDoor);
			w->scale(40,50,8);
			w->translate(77.5,50,250);
			addWall(w);

			//cieling
			dWall=DrawableEntity("Resources/mechTexture.png","resources/cube.obj");
			dWall.setNormalMap("Resources/mechNormal2.jpg");
			dWall.setShininess(5000);
		//	dWall.setScale(1,1,1);
			dWall.setUVScale(200,.5);

			w=new Wall();
			w->setModel(dWall);
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
			w->translate(91,5,75);
			w->scale(1,1,1);
			w->rotate(0,90,0);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->translate(95,2,-20);
			w->scale(.8,.8,.8);
			w->rotate(0,90,-12);
			w->setModel(d1);
			addWall(w);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(6,20,8)));
			w->translate(90,2,-20);
			w->scale(.5,.5,.5);
			w->rotate(0,180,-12);
			w->setModel(d1);
			addWall(w);

			d1=DrawableEntity(NULL,"Resources/rockMed.obj");
			d1.setDiffuseColor(.35,.35,.35);

			w=new Wall();
			w->setHitbox(CollisionBox(vec3(9,30,8)));
			w->setModel(d1);
			w->translate(-19,5,-20);
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

			addEntity(new WanderingEnemy(vec3(60,7,-10)));
			addEntity(new WanderingEnemy(vec3(63,7, 7)));

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


			//add Sun

			d=DrawableEntity(NULL,"resources/sphere.obj");
			d.setHighlightColor(1,1,1);
			d.scale(8,8,8);
			w=new Wall();
			w->translate(300,200,0);
			w->setModel(d);
			d.setAlpha(.5);
			d.scale(1.5,1.5,1.5);
			w->setModel(d,1);
			d.setScale(4,4,4);
			d.setAlpha(.8);
			d.translate(0,-15,-25);
			w->setModel(d,2);
			addWall(w);

			TVCamera* tvcamera = new TVCamera;
			//This next line does not cause the TVCamera to share the camera.
			//Instead, a copy of the camera is made. However, since the camera
			//is moved through the parenting mechanism and since the parent
			//relationship is copied too, the effect is essentially the same.
			tvcamera->cameraEntity = *currentCamera;
			//For the heck of it, let's do a top-down display!
			tvcamera->cameraEntity.rotate(-90,0,0);
			//Zoom out and slide the camera forward to account for the fact
			//that it is in behind the player.
			tvcamera->cameraEntity.translate(0,20,-10);
			addTVCamera(tvcamera);

			//We could also have set up the tvcamera entity to be a part
			//of the UI orthographic projection, thus making some kind
			//of automatic minimap/top-down view.

			TVScreen* tvscreen = new TVScreen;
			tvscreen->scale(20,20,20);
			tvscreen->translate(33,6.75,30);
			tvscreen->setTVCamera(*tvcamera);
			addEntity(tvscreen);
		}

		/** @brief called every frame to update the level elements as needed
		*/
		void update(){
			//wWalls[2]->rotate(0,1,0);
			_count+=M_PI/10;
			//wLights[0]->translate((sin(_count)),0,sin(_count));
			//std::cout<<sin(_count)<<std::endl;
			
			//Trigger event for entering the first room
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
			return _beaten;
		}
	};
}

#endif