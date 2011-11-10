#ifndef _WORLD
#define _WORLD

#include "Angel.h"

//ENGINE BASICS//
GLuint sProgram=-1;

//Key States
bool KEY_W=false;
bool KEY_A=false;
bool KEY_S=false;
bool KEY_D=false;
bool KEY_Q=false;
bool KEY_E=false;
bool KEY_SPACE=false;

int mouseX=0;
int mouseY=0;


///////////NEW//////////
//transformation locations
GLuint loc_modelTransMat=0;
GLuint loc_camTransMat=0;

//material property locations
GLuint loc_texOffset=0;
GLuint loc_texScale=0;
GLuint loc_shininess=0;
GLuint loc_texture=0;

//light property locations
GLuint loc_ambLightColor=0;
GLuint loc_lightPos=0;
GLuint loc_lightColor=0;
GLuint loc_lightFalloff=0;

void initShaderVariables(GLuint p){
	loc_modelTransMat=glGetUniformLocation(p, "vTransform");
	loc_camTransMat=glGetUniformLocation(p, "camTransform");

	loc_texOffset=glGetUniformLocation(p, "uvOffset");
	loc_texScale=glGetUniformLocation(p, "uvScale");
	loc_shininess=glGetUniformLocation(p, "shininess");
	loc_texture=glGetUniformLocation(p, "diffuseMap");

	loc_ambLightColor=glGetUniformLocation(p, "ambientColor");
	loc_lightPos=glGetUniformLocation(p, "lightPos");
	loc_lightColor=glGetUniformLocation(p, "lightColor");
	loc_lightFalloff=glGetUniformLocation(p, "lightFalloff");
}

void setModelTransMatrix(mat4 m){
	glUniformMatrix4fv(loc_modelTransMat,1,GL_FALSE,m);
}
void setCameraTransMatrix(mat4 m){
	glUniformMatrix4fv(loc_camTransMat,1,GL_FALSE,m);
}

void setTextureOffset(vec2 v){
	glUniform2f(loc_texOffset,(GLfloat)v.x,(GLfloat)v.y);
}
void setTextureScale(vec2 v){
	glUniform2f(loc_texScale,(GLfloat)v.x,(GLfloat)v.y);
}
void setShininess(float f){
	glUniform1f(loc_shininess,(GLfloat)f);
}
void setUseTexture(){
}

void setAmbientLightColor(vec3 v){
	glUniform4f(loc_texScale,(GLfloat)v.x,(GLfloat)v.y,(GLfloat)v.z,0.0);
}
void setLightPositions(vec3* lightPos,GLuint num){
	float* val=new GLfloat[num*4];
	for(int i=0;i<num;i++){
		val[4*i]=lightPos[i].x;
		val[4*i+1]=lightPos[i].y;
		val[4*i+2]=lightPos[i].z;
		val[4*i+3]=0.0;
	}
	glUniform4fv(loc_lightPos,num,val);
	delete val;
}
void setLightColors(Angel::vec3* lightCol,GLuint num){
	float* val=new GLfloat[num*4];
	for(int i=0;i<num;i++){
		val[4*i]=lightCol[i].x;
		val[4*i+1]=lightCol[i].y;
		val[4*i+2]=lightCol[i].z;
		val[4*i+3]=0.0;
	}
	glUniform4fv(loc_lightColor,num,val);
	delete val;
}
void setLightFalloff(float* lightFO, GLuint num){
	glUniform1fv(loc_lightFalloff,num,lightFO);
}

/////EndNew////////////////////////////////


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

vec3 grav;

int currentLevel=0;
//pointer to the current camera





#endif //_WORLD