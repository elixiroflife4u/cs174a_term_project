#include "General.h"

namespace Globals
{
	void initApp(){

		sProgram=InitShader("Resources/PhongShader_vertex.glsl","Resources/PhongShader_fragment.glsl");
		initShaderVariables(sProgram);

		glClearColor( .05f, .075f, .1f, 1.f );
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		//INIT THE LIGHTS
		for(int i=0;i<10;i++){
			lightPositions[i]=vec3(10,10,-10);
			lightColors[i]=vec3(1,0,0);
			lightFalloff[i]=0;
		}
	}

	void animate(){

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
		//std::cout<<"TEST"<<std::endl;
		
		setCameraTransMatrix(camera.getCameraTransformationMatrix());
		setPerspectiveMatrix(camera.getPerspectiveMatrix());
		setCameraPosition(camera.getTranslate());

		setLightPositions(lightPositions,10);
		setLightColors(lightColors,10);
		setLightFalloff(lightFalloff, 10);


		glutSetCursor(GLUT_CURSOR_NONE); //hide the cursor 

		//setCameraTransMatrix(mat4());
		//setPerspectiveMatrix(mat4());

		DrawableEntity d=DrawableEntity(NULL,"Resources/test.obj",NULL);
		d.setTranslate(0,0,-10);
		//d.setScale(1,4,1);

		d.rotate(0,90,0);
		d.draw();

		d.setTranslate(10,10,-10);
		d.setScale(.2,.2,.2);
		d.draw();


		glutSwapBuffers();
	}

	void callbackReshape(int width, int height){}
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