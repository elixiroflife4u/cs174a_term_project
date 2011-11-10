#ifndef _GENERAL
#define _GENERAL

//General Functions for setup and glut

#include <iostream>
#include "Angel.h"
#include "World.h"
#include "RenderObjectManager.h"
namespace Globals
{
	void initApp();
	void animate();
	void callbackDisplay();

	void callbackReshape(int width, int height);
	void callbackKeyboard(unsigned char key, int x, int y);
	void callbackKeyboardUp(unsigned char key, int x, int y);
	void callbackSpecialFunc(int key, int x, int y);
	void callbackSpecialUpFunc(int key, int x, int y);
	void callbackMouse(int button, int state, int x, int y);
	void callbackMotion(int x, int y);
	void callbackPassiveMotion(int x, int y);
	void callbackIdle();
	void callbackTimer(int);
}
#endif //_GENERAL
