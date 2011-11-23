#include "General.h"
#include "World.h"
#include "Engine.h"
#include "BulletEntity.h"
#include "TVScreen.h"

#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include "Text2D.h"

/** This anonymous namespace holds definitions and declarations
  * related to ordering and drawing transparent objects.
  *
  * All contents of an anonymous namespace are accessible within
  * the same file (as if they were outside of the namespace)
  * but are not exposed to other files. You can think of it as
  * being equivalent to the "static" keyword, which cannot be used
  * with classes and typedefs.
  */
namespace {
	/** This functor compares two DrawableEntity objects
	  * based on their distance from the current camera.
	  * It is meant for use with std::priority_queue, which
	  * will cause the creation of a max-heap.
	  */
	class DepthComparator {
	public:
		/** Compares two DrawableEntity objects based on their
		  * position from the camera.
		  * @return True if a is farther from the camera than b;
		  *  false otherwise.
		  */
		bool operator()(const DrawableEntity* a, const DrawableEntity* b) {
			const vec3 camPos = Globals::currentCamera->getTranslate();
			const vec3 aToCam = camPos - a->getTranslate();
			const vec3 bToCam = camPos - b->getTranslate();
			
			return dot(aToCam, aToCam) < dot(bToCam, bToCam);
		}
	};
	/** A max-heap for transparent models to enable drawing them from farthest to nearest. */
	typedef std::priority_queue<const DrawableEntity*, std::vector<const DrawableEntity*>, DepthComparator> TransparencyQueue;
}

namespace Globals
{
	void initApp(){
		//Seed the random number generator
		std::srand(std::time(NULL));

		sProgram=InitShader("Resources/PhongShader_vertex.glsl","Resources/PhongShader_fragment.glsl");
		initShaderVariables(sProgram);

		glClearColor( .05f, .075f, .1f, 1.f );
		glClearColor( .3f, .2f, .25f, 1.f ); //lightBlue Sky
		glClearColor( .7f, .9f, .9f, 1.f ); //lightBlue Sky
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//INIT THE LIGHTS
		for(int i=0;i<LIGHT_COUNT;i++){
			wLights[i]=NULL;
		}
		//Null Scenes
		for(int i=0;i<SCENE_COUNT;i++){
			wScenes[i]=NULL;
		}

		//viewFullscreen();
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2,glutGet(GLUT_WINDOW_HEIGHT)/2);
		glutSetCursor(GLUT_CURSOR_NONE);

		//setup scenes
		wScenes[0]=new Scene_1();

		wScenes[currentLevel]->setup();
	}

	static void updateEntities(GameEntityList& list) {
		GameEntityList::iterator i = list.begin();
		while(i != list.end()) {
			(*i)->update();
			
			if((*i)->toDelete()) {
				delete *i;
				i = list.erase(i);
				continue;
			}

			++i;
		}
	}
	static void checkCollisionsSelf(GameEntityList& list) {
		for(GameEntityList::iterator i = list.begin(); i != list.end(); ++i) {
NEXT_I:
			GameEntityList::iterator j = i;
			for(++j; j != list.end(); ++j) {
NEXT_J:
				//if one occurs then complete the action for both
				if((*i)->didCollide(**j)){
					(*i)->onCollide(**j);
					(*j)->onCollide(**i);

					const bool deleteI = (*i)->toDelete(),
					           deleteJ = (*j)->toDelete();
					if(deleteJ) {
						delete *j;
						j = list.erase(j);
					}
					if(deleteI) {
						delete *i;
						i = list.erase(i);
						if(i == list.end()) return;
						goto NEXT_I;
					} else if(deleteJ) {
						if(j == list.end()) break;
						goto NEXT_J;
					}
				}
			}
		}
	}
	static void checkCollisions(GameEntityList& listA, GameEntityList& listB) {
		assert(&listA != &listB);
		for(GameEntityList::iterator i = listA.begin(); i != listA.end(); ++i) {
NEXT_I:
			for(GameEntityList::iterator j = listB.begin(); j != listB.end(); ++j) {
NEXT_J:
				//if one occurs then complete the action for both
				if((*i)->didCollide(**j)){
					(*i)->onCollide(**j);
					(*j)->onCollide(**i);

					const bool deleteI = (*i)->toDelete(),
					           deleteJ = (*j)->toDelete();
					if(deleteJ) {
						delete *j;
						j = listB.erase(j);
					}
					if(deleteI) {
						delete *i;
						i = listA.erase(i);
						if(i == listA.end()) return;
						goto NEXT_I;
					} else if(deleteJ) {
						if(j == listB.end()) break;
						goto NEXT_J;
					}
				}
			}
		}
	}

	void animate(){
		frameCount++;
		updateEntities(wEntities);
		updateEntities(wWalls);
		updateEntities(wSoftEntities);

		checkCollisionsSelf(wEntities);
		checkCollisions(wEntities, wWalls);
		checkCollisions(wEntities, wSoftEntities);
		checkCollisions(wWalls, wSoftEntities);

		//update everything in the level that needs to be updated
		wScenes[currentLevel]->update();
		if(wScenes[currentLevel]->levelEnd()){

		}

		//Update the mouse flags
		MOUSE_EDGE_LEFT = MOUSE_EDGE_RIGHT = false;
	}

	/** Draws opaque models from an list of GameEntity pointers, pushing transparent
	  * models onto a given queue.
	  * @param list A list of GameEntity object pointers.
	  * @param transparencyQueue The queue onto which to push transparent models.
	  */
	static void drawOpaqueEntities(const Globals::GameEntityList& list, TransparencyQueue& transparencyQueue) {
		for(Globals::GameEntityList::const_iterator i = list.begin(); i != list.end(); ++i) {
			for(int c = 0; c < GameEntity::MAX_MODELS; c++) {
				const DrawableEntity& model = (*i)->getModelConst(c);
				if(&model != NULL) {
					if(model.isAlphaRequired())
						transparencyQueue.push(&model);
					else
						model.draw();
				}
			}
		}
	}

	static void render()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the draw buffer

		glEnable( GL_BLEND );

		currentCamera->setAspectRatio(resolution.x/resolution.y);
		setCameraTransMatrix(currentCamera->getCameraTransformationMatrix());
		setPerspectiveMatrix(currentCamera->getPerspectiveMatrix());
		setCameraPosition(currentCamera->getTranslate());
		setLights(wLights,LIGHT_COUNT);
		setAmbientLightColor(vec3(.1,.05,.075));
		setAmbientLightColor(vec3(.1,.1,.2));


		//Draw non-transparent models, pushing transparent ones onto a max-heap
		TransparencyQueue transparencyQueue;
		drawOpaqueEntities(wEntities, transparencyQueue); //Draw Every GameEntity
		drawOpaqueEntities(wWalls, transparencyQueue); //Draw Every Wall
		drawOpaqueEntities(wSoftEntities, transparencyQueue);

		//Draw transparent models, furthest from camera first
		//Disable updating the z-buffer, but still conduct the
		//test so that nearer opaque objects completely occlude
		//farther transparent objects.

		glEnable( GL_BLEND );
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		while(!transparencyQueue.empty()) {
			transparencyQueue.top()->draw();
			transparencyQueue.pop();
		}
		glDepthMask(GL_TRUE);
		
		

		//UI hack
		setAmbientLightColor(vec3(1,1,1));
		setCameraTransMatrix(mat4());
		setPerspectiveMatrix(currentCamera->getOrthographicMatrix());
		setCameraPosition(vec3(0,0,.5));

		Wall w=Wall();
		w.translate(-(.4)*(resolution.x/resolution.y),.48,-10);
		w.scale((Globals::getPlayer()->getHealth()/Player::MAX_HEALTH)*.5,.025,.1);

		DrawableEntity d=DrawableEntity(NULL,"Resources/cube.obj");
		d.translate(.5,0,0);
		d.setAlpha(.75);

		w.setModel(d);
		w.draw();

		w.translate(0,-.02,0);
		w.setScale((Globals::getPlayer()->getShieldCharge()/Player::MAX_SHIELD)*.5,.01,.1);
		w.draw();

		Globals::setModelTransMatrix(mat4());
		Text2D n; 
		n.draw_stuff("HEALTH",vec4(1,1,1,1), -0.495*(resolution.x/resolution.y), .4725 );
		n.draw_stuff("SHIELD",vec4(1,1,1,1), -0.495*(resolution.x/resolution.y), .449 );

		char* weaponText="";
		switch(getPlayer()->getWeapon()){
		case 2:
			weaponText="CURVY BOOLET";
			break;
		case 0:
			weaponText="MACHINE GUN";
			break;
		case 1:
			weaponText="MORTAR";
			break;

		}
		n.draw_stuff(weaponText,vec4(1,1,1,1), -0.495*(resolution.x/resolution.y), .449-(.4725-.449) );

		glDisable(GL_BLEND);
	}

	void callbackDisplay() {
		//Render all the TVCameras.
		CameraEntity* const originalCamera = currentCamera;
		for(TVCameraList::iterator i = wTVCameras.begin(); i != wTVCameras.end(); ++i) {
			currentCamera = &(*i)->cameraEntity;
			(*i)->framebuffer.render(&render, 160, 160);
		}
		currentCamera = originalCamera;

		//Render to the screen.
		render();
		glutSwapBuffers();
	}

	void callbackReshape(int width, int height){
		setResolution(width,height);
	}
	static void setKey(unsigned char key, bool val) {
		switch (key){
		case 'A':
		case 'a':
			Globals::KEY_A = val;
			break;
		case 'W':
		case 'w':
			Globals::KEY_W = val;
			break;
		case 'S':
		case 's':
			Globals::KEY_S = val;
			break;//
		case 'D':
		case 'd':
			Globals::KEY_D = val;
			break;
		case 'Q':
		case 'q':
			Globals::KEY_Q = val;
			break;
		case 'E':
		case 'e':
			Globals::KEY_E = val;
			break;
		case ' ':
			Globals::KEY_SPACE = val;
			break;
		case ';':
			viewFullscreen();
			break;
		case '\'':
			if(!val)firstPerson=!firstPerson;
			break;
		case 'O':
		case 'o':
			universalNormalMapDepthMult+=.1;
			break;
		case 'P':
		case 'p':
			universalNormalMapDepthMult-=.1;
			break;
		case 'k':
		case 'K':
			setHasFog(false);
			break;
		case 'l':
		case 'L':
			setHasFog(true);
			break;
		}
	}
	void callbackKeyboard(unsigned char key, int x, int y){
		if(key == 27) exit(0); //quit on esc
		else setKey(key, true);
	}
	void callbackKeyboardUp(unsigned char key, int x, int y){
		setKey(key, false);
	}
	void callbackSpecialFunc(int key, int x, int y){

	}
	void callbackSpecialUpFunc(int key, int x, int y){

	}
	void callbackMouse(int button, int state, int x, int y){
		const bool down = (state == GLUT_DOWN);
		switch(button) {
		case GLUT_LEFT_BUTTON:
			MOUSE_EDGE_LEFT = down && !MOUSE_LEFT;
			MOUSE_LEFT = down;
			break;
		case GLUT_RIGHT_BUTTON:
			MOUSE_EDGE_RIGHT = down && !MOUSE_RIGHT;
			MOUSE_RIGHT = down;
			break;
		}
	}
	void callbackMotion(int x, int y){
		Globals::mouseX = x;
		Globals::mouseY = y;
	}
	void callbackPassiveMotion(int x, int y){
		Globals::mouseX = x;
		Globals::mouseY = y;
	}
	void callbackIdle(){}
	void callbackTimer(int) // Called when the timer expires
	{
		glutTimerFunc(1000/30, callbackTimer, 0);
		animate();
		glutPostRedisplay();
	}
}