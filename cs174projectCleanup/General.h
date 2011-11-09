#ifndef _GENERAL
#define _GENERAL

//General Functions for setup and glut

#include <iostream>
#include "Angel.h"
#include "World.h"

#include "RenderObjectManager.h"

void initApp(){
	sProgram=InitShader("Resources/PhongShader_vertex.glsl","Resources/PhongShader_fragment.glsl");

	glClearColor( .05, .075, .1, 1 );
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
void callbackKeyboard(unsigned char key, int x, int y){
	switch (key){
	case 27: //esc
		exit(0);
		break;
	}
}
void callbackKeyboardUp(unsigned char key, int x, int y){

}
void callbackSpecialFunc(int key, int x, int y){

}
void callbackSpecialUpFunc(int key, int x, int y){

}
void callbackMouse(int button, int state, int x, int y){

}
void callbackMotion(int x, int y){

}
void callbackPassiveMotion(int x, int y){

}
void callbackIdle(){}
void callbackTimer(int) // Called when the timer expires
{
	glutTimerFunc(1000/30, callbackTimer, 0);
	glutPostRedisplay();
}

#endif //_GENERAL
