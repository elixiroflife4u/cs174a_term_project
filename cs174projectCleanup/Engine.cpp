#include "Engine.h"

namespace Globals
{	
	bool useText = false;

//ENGINE BASICS//
	GLuint sProgram=0;
	CameraEntity defaultCamera;
	CameraEntity*  currentCamera=&defaultCamera;
	unsigned int frameCount = 0;
	float universalNormalMapDepthMult=1;

	vec3 lightPositions[10];
	float lightFalloff[10];
	vec3 lightColors[10];


	//Key States
	bool KEY_W=false;
	bool KEY_A=false;
	bool KEY_S=false;
	bool KEY_D=false;
	bool KEY_Q=false;
	bool KEY_E=false;
	bool KEY_SPACE=false;

	//Mouse button states
	bool MOUSE_LEFT = false, MOUSE_EDGE_LEFT = false;
	bool MOUSE_RIGHT = false, MOUSE_EDGE_RIGHT = false;

	int mouseX=0;
	int mouseY=0;

	vec2 resolution=vec2(100,100);

	void setResolution(vec2 v){
		resolution=v;
		glViewport(0,0,v.x,v.y);
	}
	void setResolution(int width, int height){
		setResolution(vec2(width,height));
	}
	void viewWindowed(int x, int y, int width, int height){
		glutPositionWindow(x,y);
		glutReshapeWindow(width,height);
	}
	void viewFullscreen(){
		glutFullScreen();
	}

	vec3 _ambColor;

	//transformation locations
	GLuint loc_modelTransMat=0;
	GLuint loc_camTransMat=0;
	GLuint loc_perspTransMat=0;
	GLuint loc_camPosition=0;

	//material property locations
	GLuint loc_texOffset=0;
	GLuint loc_texScale=0;
	GLuint loc_shininess=0;
	GLuint loc_texture=0;
	GLuint loc_hasTex=0;
	GLuint loc_normalMap=0;
	GLuint loc_normalDepth=0;
	GLuint loc_diffColor=0;
	GLuint loc_alpha=0;

	//light property locations
	GLuint loc_ambLightColor=0;
	GLuint loc_lightPos=0;
	GLuint loc_lightColor=0;
	GLuint loc_lightFalloff=0;
	GLuint loc_lightBrightness=0;

	//fog variable location
	GLuint loc_hasFog;

	void initShaderVariables(GLuint p){
		loc_modelTransMat=glGetUniformLocation(p, "vTransform");
		loc_camTransMat=glGetUniformLocation(p, "camTransform");
		loc_perspTransMat=glGetUniformLocation(p, "perspTransform");
		loc_camPosition=glGetUniformLocation(p, "camPos");

		loc_texOffset=glGetUniformLocation(p, "uvOffset");
		loc_texScale=glGetUniformLocation(p, "uvScale");
		loc_shininess=glGetUniformLocation(p, "shininess");
		
		loc_texture=glGetUniformLocation(p, "diffuseMap");
		loc_hasTex=glGetUniformLocation(p, "hasTexture");
		loc_normalMap=glGetUniformLocation(p, "NormalMap");
		glUniform1i(loc_texture,0);
		glUniform1i(loc_normalMap,1);
		loc_normalDepth=glGetUniformLocation(p, "normalMapDepth");

		loc_diffColor=glGetUniformLocation(p, "diffuseColor");
		loc_alpha=glGetUniformLocation(p, "alpha");

		loc_ambLightColor=glGetUniformLocation(p, "ambientColor");
		loc_lightPos=glGetUniformLocation(p, "lightPos");
		loc_lightColor=glGetUniformLocation(p, "lightColor");
		loc_lightFalloff=glGetUniformLocation(p, "lightFalloff");
		loc_lightBrightness=glGetUniformLocation(p, "lightBrightness");

		loc_hasFog=glGetUniformLocation(p, "hasFog");;
	}

	void setModelTransMatrix(mat4 m){
		glUniformMatrix4fv(loc_modelTransMat,1,GL_FALSE,m);
	}
	void setCameraTransMatrix(mat4 m){
		glUniformMatrix4fv(loc_camTransMat,1,GL_FALSE,m);
	}
	void setPerspectiveMatrix(mat4 m){
		glUniformMatrix4fv(loc_perspTransMat,1,GL_FALSE,m);
	}
	void setCameraPosition(vec3 v){
		glUniform4f(loc_camPosition,v.x,v.y,v.z,1.0);
	}

	void setTextureOffset(vec2 v){
		glUniform2f(loc_texOffset,(GLfloat)v.x,(GLfloat)v.y);
	}
	void setTextureScale(vec2 v){
		glUniform2f(loc_texScale,(GLfloat)v.x,(GLfloat)v.y);
	}
	void setHasTexture(bool t){
		glUniform1i(loc_hasTex,t);
	}
	void setShininess(float f){
		glUniform1f(loc_shininess,(GLfloat)f);
	}
	void setUseTexture(GLuint i){
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,i);
	}
	void setUseTexture(char* t){
		glActiveTexture(GL_TEXTURE0);
		CTextureManager::GetInstance()->GetTexture(t)->Bind();
	}
/*	void setUseNormalMap(GLuint i){

	}*/
	void setUseNormalMap(char* t){
		glActiveTexture(GL_TEXTURE1);
		CTextureManager::GetInstance()->GetTexture(t)->Bind();
	}
	void setNormalMapDepth(float f){
		glUniform1f(loc_normalDepth,(GLfloat)f*universalNormalMapDepthMult);
	}

	void setDiffuseColor(vec3 c){
		glUniform4f(loc_diffColor,c.x,c.y,c.z,0.0);
	}
	void setAlpha(float a){
		glUniform1f(loc_alpha,a);
	}

	void drawModel(char* m){
		CRenderObjectManager::GetInstance()->GetRenderObject(m)->draw();
	}


	void setAmbientLightColor(vec3 v){
		_ambColor=v;
		glUniform4f(loc_ambLightColor,(GLfloat)v.x,(GLfloat)v.y,(GLfloat)v.z,1.0);
	}
	vec3 getAmbientColor(){return _ambColor;}

	void setLightPositions(vec3* lightPos,GLuint num){
		float* val=new GLfloat[num*4];
		for(int i=0;i<num;i++){
			val[4*i]=lightPos[i].x;
			val[4*i+1]=lightPos[i].y;
			val[4*i+2]=lightPos[i].z;
			val[4*i+3]=1.0;
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
			val[4*i+3]=1.0;
		}
		glUniform4fv(loc_lightColor,num,val);
		delete val;
	}
	void setLightFalloff(float* lightFO, GLuint num){
		glUniform1fv(loc_lightFalloff,num,lightFO);
	}
	void setLightBrightness(float* b, GLuint num){
		glUniform1fv(loc_lightBrightness,num,b);
	}

	void setLights(PointLight** pl, GLuint num){
		vec3* lPos=new vec3[num];
		vec3* lCol=new vec3[num];
		float* lFallOff=new float[num];
		float* lBrightness=new float[num];

		for(int i=0;i<num;i++){
			if(pl[i]!=NULL){
				lPos[i]=pl[i]->getTranslate();
				lCol[i]=pl[i]->getColor();
				lFallOff[i]=pl[i]->getFalloff();
				lBrightness[i]=pl[i]->getBrightness();
			}else{
				lPos[i]=vec3(0,0,0);
				lCol[i]=vec3(0,0,0);
				lFallOff[i]=1.0;
				lBrightness[i]=0.0;
			}
		}

		setLightPositions(lPos,num);
		setLightColors(lCol,num);
		setLightFalloff(lFallOff,num);
		setLightBrightness(lBrightness, num);

		delete lPos;
		delete lCol;
		delete lFallOff;
		delete lBrightness;

	}

	void setHasFog(bool f){
		glUniform1f(loc_hasFog,f);
	}


}