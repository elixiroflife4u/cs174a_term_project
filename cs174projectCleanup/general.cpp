#include "General.h"

namespace Globals
{
	void initApp(){

			sProgram=InitShader("Resources/PhongShader_vertex.glsl","Resources/PhongShader_fragment.glsl");

		glClearColor( .05f, .075f, .1f, 1.f );
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		CRenderObjectManager::GetInstance()->GetRenderObject("Resources/test.obj")->activateObject(sProgram);
	}
	void animate(){

	}
	void callbackDisplay()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the draw buffer
		//std::cout<<"TEST"<<std::endl;
		CRenderObjectManager::GetInstance()->GetRenderObject("Resources/test.obj")->draw();
		glutSwapBuffers();
	}

	void callbackReshape(int width, int height){}
	static void setKey(unsigned char key, bool val) {
		switch (key){
		case 'A':
		case 'a':
			Globals::KEY_W = val;
			break;
		case 'W':
		case 'w':
			Globals::KEY_A = val;
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
		glutPostRedisplay();
	}
}