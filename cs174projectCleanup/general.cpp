#include "General.h"
#include "World.h"
#include "Engine.h"

#include <queue>

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
			
			return dot(aToCam, aToCam) > dot(bToCam, bToCam);
		}
	};
	/** A max-heap for transparent models to enable drawing them from farthest to nearest. */
	typedef std::priority_queue<const DrawableEntity*, std::vector<const DrawableEntity*>, DepthComparator> TransparencyQueue;
	/** Draws opaque models from an array of GameEntity pointers, pushing transparent
	  * models onto a given queue.
	  * @tparam T The actual type of GameEntities (use to permit iterating through
	  *  an array of child class objects.
	  * @param arr An array of GameEntity (or child class) object pointers.
	  * @param count Length of the array.
	  * @param transparencyQueue The queue onto which to push transparent models.
	  */
	template<typename T>
	void drawOpaqueEntities(const T* const arr[], int count, TransparencyQueue& transparencyQueue) {
		for(int i = 0; i < count; ++i) {
			if(arr[i] != NULL) {
				for(int i = 0; i < T::MAX_MODELS; ++i) {
					const DrawableEntity* model = arr[i]->getModelConst(i);
					if(model->getAlphaFlag())
						transparencyQueue.push(model);
					else
						model->draw();
				}
			}
		}
	}
}

namespace Globals
{
	void initApp(){

		sProgram=InitShader("Resources/PhongShader_vertex.glsl","Resources/PhongShader_fragment.glsl");
		initShaderVariables(sProgram);

		glClearColor( .05f, .075f, .1f, 1.f );
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//INIT THE LIGHTS
		for(int i=0;i<LIGHT_COUNT;i++){
			wLights[i]=NULL;
		}
		//Null Walls
		for(int i=0;i<WALL_COUNT;i++){
			wWalls[i]=NULL;
		}
		//Null GameEntities
		for(int i=0;i<GAMEENTITY_COUNT;i++){
			wEntities[i]=NULL;
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

	void animate(){
		//Update every gameEntity
		for(int i=0;i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]!=NULL){
				wEntities[i]->update();
			}
		}
		//Udpate every wall
		for(int i=0;i<WALL_COUNT;i++){
			if(wWalls[i]!=NULL){
				wWalls[i]->update();
			}
		}

		//Check for collision between every gameEntity
		for(int i=0;i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]!=NULL){
				//check against every gameentity for a collision
				for(int j=i+1;j<GAMEENTITY_COUNT;j++){
					if(wEntities[j]!=NULL){
						//if one occurs then complete the action for both
						if(wEntities[i]->didCollide(*wEntities[j])){
							wEntities[i]->onCollide(*wEntities[j]);
							wEntities[j]->onCollide(*wEntities[i]);
						}
					}
				}
			}
		}
		//Check for collision between every gameEntity and a wall
		for(int i=0;i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]!=NULL){
				for(int j=0;j<WALL_COUNT;j++){
					if(wWalls[j]!=NULL){
						if(wEntities[i]->didCollide(*wWalls[j])){
							std::cout<<j<<": ";
							wEntities[i]->onCollide(*wWalls[j]);
							wWalls[j]->onCollide(*wEntities[i]);
						}
					}
				}
			}
		}

		//update everything in the level that needs to be updated
		wScenes[currentLevel]->update();
		if(wScenes[currentLevel]->levelEnd()){

		}


		int xDelta=mouseX-glutGet(GLUT_WINDOW_WIDTH)/2;
		int yDelta=mouseY-glutGet(GLUT_WINDOW_HEIGHT)/2;

		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2,glutGet(GLUT_WINDOW_HEIGHT)/2);

		wEntities[0]->rotate(0,-xDelta/10,0);
		wEntities[0]->rotate(-yDelta/10,0,0);

		/*if(KEY_Q)wEntities[0]->translate(0,-.1,0);
		if(KEY_E)wEntities[0]->translate(0,.1,0);
		if(KEY_W)wEntities[0]->translate(0,0,-.1);
		if(KEY_S)wEntities[0]->translate(0,0,.1);
		if(KEY_D)wEntities[0]->translate(.1,0,0);
		if(KEY_A)wEntities[0]->translate(-.1,0,0);*/
	}
	void callbackDisplay()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the draw buffer
		
		currentCamera->setAspectRatio(resolution.x/resolution.y);
		setCameraTransMatrix(currentCamera->getCameraTransformationMatrix());
		setPerspectiveMatrix(currentCamera->getPerspectiveMatrix());
		setCameraPosition(currentCamera->getTranslate());
		setLights(wLights,LIGHT_COUNT);

		//Draw non-transparent models, pushing transparent ones onto a max-heap
		TransparencyQueue transparencyQueue;
		drawOpaqueEntities(wEntities, GAMEENTITY_COUNT, transparencyQueue); //Draw Every GameEntity
		drawOpaqueEntities(wWalls, WALL_COUNT, transparencyQueue); //Draw Every Wall

		//Draw transparent models, furthest from camera first
		while(!transparencyQueue.empty()) {
			transparencyQueue.top()->draw();
			transparencyQueue.pop();
		}

		DrawableEntity d=DrawableEntity(NULL,"Resources/test.obj",NULL);
		d.setTranslate(0,0,-10);
		//d.setScale(1,4,1);
		d.setDiffuseColor(vec3(1,0,0));

		d.rotate(0,90,0);
		d.draw();

		d.setTranslate(10,10,-10);
		d.setScale(.2,.2,.2);
		d.draw();


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
			break;
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