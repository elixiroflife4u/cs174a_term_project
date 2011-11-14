#include "General.h"
#include "World.h"
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
					}else{
						break;
					}
				}
			}else{
				break;
			}
		}

		//update everything in the level that needs to be updated
		wScenes[currentLevel]->update();
		if(wScenes[currentLevel]->levelEnd()){

		}


		int xDelta=mouseX-glutGet(GLUT_WINDOW_WIDTH)/2;
		int yDelta=mouseY-glutGet(GLUT_WINDOW_HEIGHT)/2;

		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH)/2,glutGet(GLUT_WINDOW_HEIGHT)/2);

		camera.rotate(0,-xDelta/10,0);
		camera.rotate(-yDelta/10,0,0);

		if(KEY_Q)camera.translate(0,-.5,0);
		if(KEY_E)camera.translate(0,.5,0);
		if(KEY_W)camera.translate(0,0,-.5);
		if(KEY_S)camera.translate(0,0,.5);
		if(KEY_D)camera.translate(.5,0,0);
		if(KEY_A)camera.translate(-.5,0,0);
	}
	void callbackDisplay()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the draw buffer
		
		camera.setAspectRatio(resolution.x/resolution.y);
		setCameraTransMatrix(camera.getCameraTransformationMatrix());
		setPerspectiveMatrix(camera.getPerspectiveMatrix());
		setCameraPosition(camera.getTranslate());
		setLights(wLights,LIGHT_COUNT);

		//DrawCode goes Here
		//Draw Every GameEntity
		for(int i=0;i<GAMEENTITY_COUNT;i++){
			if(wEntities[i]!=NULL){
				wEntities[i]->draw();
			}else{
				break;
			}
		}
		//Draw Every Wall
		for(int i=0;i<WALL_COUNT;i++){
			if(wWalls[i]!=NULL){
				wWalls[i]->draw();
			}else{
				break;
			}
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