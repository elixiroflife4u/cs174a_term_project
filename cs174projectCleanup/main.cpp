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
#include "SoundPlayer.h"
#include "General.h"
#include <cstring>


using namespace Globals;

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

	//Enable text if command line parameter present
	for(int i = 1; i < argc; ++i) {
		if(strcmp(argv[i], "--text") == 0) {
			Globals::useText = true;
			break;
		}
	}

	SoundPlayerGuard spg;
	if(spg.initialized) {
			if(!SoundPlayer::playBackground("resources/cl1.midi"))
				std::cerr<<"could not play file cl1.midi. \n";
			if(!SoundPlayer::loadSound("resources/curvy.wav"))
				std::cerr<<"could not play file curvy.way. \n";
			if(!SoundPlayer::loadSound("resources/cannon.wav"))
				std::cerr<<"could not play file cannon.wav. \n";
			if(!SoundPlayer::loadSound("resources/death.wav"))
				std::cerr<<"could not play file death.wav. \n";
			if(!SoundPlayer::loadSound("resources/fireball.wav"))
				std::cerr<<"could not play file fireball.wav . \n";
			if(!SoundPlayer::loadSound("resources/jump.wav"))
				std::cerr<<"could not play file jump.wav. \n";
	} else {
		std::cerr<<"SoundPlayer failed to initialize.\n";
	}
	//start glut main loop
	glutMainLoop();
	return 0;
}