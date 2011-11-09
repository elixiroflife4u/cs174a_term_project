/*#include "windows\glew\include\GL\glew.h"
#include "windows\glut\glut.h"
#include "CollisionBox.h"
#include "EnvironmentEntity.h"
#include "GameEntity.h"
#include "Globals.h"
#include "MobileEntity.h"
#include "Player.h"
#include "WorldEntity.h"
*/
//#include "GL\glew.h"
//#include "GL\glut.h"
#include "IL\il.h"

#include "General.h"

void initGlut(int& argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 50);
	glutInitWindowSize(600, 600);
	glutCreateWindow("G Test");
}

void initCallbacks()
{
	glutDisplayFunc(callbackDisplay);
	glutReshapeFunc(callbackReshape);
	glutKeyboardFunc(callbackKeyboard);
	glutKeyboardUpFunc(callbackKeyboardUp);
	glutSpecialFunc(callbackSpecialFunc);
	glutSpecialUpFunc(callbackSpecialUpFunc);
	glutMouseFunc(callbackMouse);
	glutMotionFunc(callbackMotion);
	glutPassiveMotionFunc(callbackPassiveMotion);
	glutIdleFunc(callbackIdle);
	glutTimerFunc(1000/30, callbackTimer, 0);
}

int main(int argc, char** argv){
	//initialize glut and glew
	initGlut(argc, argv);
	glewInit();
	ilInit();
	initApp();

	initCallbacks();

	//start glut main loop
	glutMainLoop();
	return 0;



	return 0;
}