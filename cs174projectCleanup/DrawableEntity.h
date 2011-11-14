#ifndef _DRAWABLEENTITY
#define _DRAWABLEENTITY

#include "WorldEntity.h"
#include "Engine.h"
class DrawableEntity:public WorldEntity{
private:
	char* _texName;
	vec3 _diffuseColor;
	char* _modelName;
	vec2 _uvOffset;
	vec2 _uvScale;
	float _shininess;
public:
	inline DrawableEntity(char* tn, char* mn, WorldEntity* parent=NULL)
		:_texName(tn),_modelName(mn),WorldEntity(parent),_uvScale(vec2(1,1)),_uvOffset(vec2(0,0)),_shininess(0),_diffuseColor(vec3(0,1,0))
	{
		if(tn!=NULL)CTextureManager::GetInstance()->GetTexture(tn);
		if(mn!=NULL)CRenderObjectManager::GetInstance()->GetRenderObject(mn)->activateObject(Globals::sProgram);
	}
	inline void draw(){
		Globals::setTextureOffset(_uvOffset);
		Globals::setTextureScale(_uvScale);
		Globals::setShininess(_shininess);

		if(_texName!=NULL){
			Globals::setUseTexture(_texName);
			Globals::setDiffuseColor(vec3(0,0,0));
		}else {
			Globals::setUseTexture(0);
			Globals::setDiffuseColor(_diffuseColor);
		}

		Globals::setModelTransMatrix(getTransformationMatrix());

		if(_modelName!=NULL)Globals::drawModel(_modelName);

	}
	inline void setShininess(float f){_shininess=f;}
	inline void setTexture(char* t){_texName=t;if(t=="")_texName=NULL;}
	inline void setDiffuseColor(vec3 c){_diffuseColor=c;_texName=NULL;}
	inline void setDiffuseColor(float r, float g, float b){setDiffuseColor(vec3(r,g,b));}
	inline void setModel(char* m){_modelName=m;}
	inline void setUVOffset(float u, float v){_uvOffset=vec2(u,v);}
	inline void setUVScale(float u, float v){_uvScale=vec2(u,v);}

};

#endif