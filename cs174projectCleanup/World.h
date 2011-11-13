#ifndef _WORLD
#define _WORLD

#include "Angel.h"
#include "TextureManager.h"
#include "RenderObjectManager.h"
#include "CameraEntity.h"

namespace Globals
{
	//ENGINE BASICS//
	extern GLuint sProgram;
	extern CameraEntity camera;
	extern vec3 lightPositions[10];
	extern float lightFalloff[10];
	extern vec3 lightColors[10];


	//Key States
	extern bool KEY_W;
	extern bool KEY_A;
	extern bool KEY_S;
	extern bool KEY_D;
	extern bool KEY_Q;
	extern bool KEY_E;
	extern bool KEY_SPACE;

	extern int mouseX;
	extern int mouseY;

	extern GLuint loc_modelTransMat;
	extern GLuint loc_camTransMat;

	//material property locations
	extern GLuint loc_texOffset;
	extern GLuint loc_texScale;
	extern GLuint loc_shininess;
	extern GLuint loc_texture;

	//light property locations
	extern GLuint loc_ambLightColor;
	extern GLuint loc_lightPos;
	extern GLuint loc_lightColor;
	extern GLuint loc_lightFalloff;

	void initShaderVariables(GLuint p);

	void setModelTransMatrix(mat4 m);
	void setCameraTransMatrix(mat4 m);
	void setPerspectiveMatrix(mat4 m);
	void setCameraPosition(vec3 v);

	void setTextureOffset(vec2 v);
	void setTextureScale(vec2 v);
	void setShininess(float f);
	void setUseTexture(int i);
	void setUseTexture(char* t);
	void drawModel(char* m);

	void setAmbientLightColor(vec3 v);
	void setLightPositions(vec3* lightPos,GLuint num);
	void setLightColors(Angel::vec3* lightCol,GLuint num);
	void setLightFalloff(float* lightFO, GLuint num);
	
	//FOR OUR GAME//
	//Include Bullets
	//Include Walls
	//Include MainChar
	//Include GameEntity

	//Array of Walls
	//Array of Bullets
	//Array of GameEntities
	//Array of Scenes
	//transparent object heap

	extern vec3 grav;

	extern int currentLevel;
	//pointer to the current camera
}

#endif //_WORLD