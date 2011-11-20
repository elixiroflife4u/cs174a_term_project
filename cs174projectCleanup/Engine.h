#ifndef _ENGINE
#define _ENGINE

#include "Angel.h"
#include "TextureManager.h"
#include "RenderObjectManager.h"
#include "CameraEntity.h"
#include "PointLight.h"

namespace Globals
{
	//ENGINE BASICS//
	extern GLuint sProgram;
	extern CameraEntity defaultCamera;
	extern CameraEntity*  currentCamera;

	extern unsigned int frameCount;

	//Key States
	extern bool KEY_W;
	extern bool KEY_A;
	extern bool KEY_S;
	extern bool KEY_D;
	extern bool KEY_Q;
	extern bool KEY_E;
	extern bool KEY_SPACE;

	//Mouse button states
	extern bool MOUSE_LEFT, ///< True if left mouse button is down now.
		MOUSE_EDGE_LEFT; ///< True if left mouse button transitioned to down this frame. Updated by Globals::animate().
	extern bool MOUSE_RIGHT, ///< True if right mouse button is down now.
		MOUSE_EDGE_RIGHT; ///< True if right mouse button transitioned to down this frame. Updated by Globals::animate().

	extern int mouseX;
	extern int mouseY;

	extern vec2 resolution;

	void setResolution(vec2 v);
	void setResolution(int width, int height);
	void viewWindowed(int x, int y, int width, int height);
	void viewFullscreen();

	extern vec3 _ambColor;

	extern GLuint loc_modelTransMat;
	extern GLuint loc_camTransMat;

	//material property locations
	extern GLuint loc_texOffset;
	extern GLuint loc_texScale;
	extern GLuint loc_shininess;
	extern GLuint loc_texture;
	extern GLuint loc_hasTex;
	extern GLuint loc_normalMap;
	extern GLuint loc_diffColor;
	extern GLuint loc_alpha;

	//light property locations
	extern GLuint loc_ambLightColor;
	extern GLuint loc_lightPos;
	extern GLuint loc_lightColor;
	extern GLuint loc_lightFalloff;
	extern GLuint loc_lightBrightness;

	void initShaderVariables(GLuint p);

	void setModelTransMatrix(mat4 m);
	void setCameraTransMatrix(mat4 m);
	void setPerspectiveMatrix(mat4 m);
	void setCameraPosition(vec3 v);

	void setTextureOffset(vec2 v);
	void setTextureScale(vec2 v);
	void setHasTexture(bool t);
	void setShininess(float f);
	//void setUseNormalMap(GLuint i);
	void setUseNormalMap(char* t);
	void setNormalMapDepth(float f);

	void setUseTexture(GLuint i);
	void setUseTexture(char* t);
	void setDiffuseColor(vec3 c);
	void setAlpha(float a);

	void drawModel(char* m);

	void setAmbientLightColor(vec3 v);
	vec3 getAmbientColor();

	void setLightPositions(vec3* lightPos,GLuint num);
	void setLightColors(Angel::vec3* lightCol,GLuint num);
	void setLightFalloff(float* lightFO, GLuint num);
	void setLightBrightness(float* b, GLuint num);

	void setLights(PointLight** pl, GLuint num);

}

#endif //_ENGINE