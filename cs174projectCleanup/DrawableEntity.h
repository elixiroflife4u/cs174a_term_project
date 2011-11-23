#ifndef _DRAWABLEENTITY
#define _DRAWABLEENTITY

#include "WorldEntity.h"
#include "Engine.h"

/** @brief This class represents an object than can be directly drawn on screen.
  * Most other rendered objects are rendered on screen only in the sense that
  * they in fact hold any number of DrawableEntity objects. Note, however,
  * that the geometry of the object and the instructions that actually push
  * it down the pipeline come from the RenderObject.
  */
class DrawableEntity:public WorldEntity{
private:
	union {
		char* _texName; ///< Pathname of the texture map.
		GLuint _texId;   ///< Texture ID
	};
	bool useTexId;

	char* _normalMapName; ///< Pathname of the normal map.

	vec3 _diffuseColor;  ///< Diffuse color.
	vec3 _highlightColor;  ///< Specular color.

	float _normalMapDepth; ///< Depth of the normal map.

	float _alpha; ///< Entity wide alpha value. Combined with texture map for ultimate transparency.
	char* _modelName; ///< Pathname of the model. Used to look up render object.
	vec2 _uvOffset; ///< Offset in the texture map.
	vec2 _uvScale; ///< Scale factor to apply to the texture map.
	float _shininess; ///< Shininess factor used for specular highlights.

	bool _alphaFlag; ///< True if object needs special transparency treatment when drawn to ensure proper ordering.

public:
	inline DrawableEntity(char* tn, char* mn, WorldEntity* parent=NULL)
		:WorldEntity(parent),useTexId(false),_uvScale(vec2(1,1)),_uvOffset(vec2(0,0)),_shininess(0),_diffuseColor(vec3(0,1,0)),_alpha(1.0),_alphaFlag(false),_normalMapName(NULL),_normalMapDepth(0),_highlightColor(vec3(0,0,0))
	{
		setTexture(tn);
		setModel(mn);
		
		if(tn!=NULL)CTextureManager::GetInstance()->GetTexture(tn);
		if(mn!=NULL)CRenderObjectManager::GetInstance()->GetRenderObject(mn)->activateObject(Globals::sProgram);
	}
	inline void draw()const{
		Globals::setTextureOffset(_uvOffset);
		Globals::setTextureScale(_uvScale);
		Globals::setShininess(_shininess);

		if(useTexId) {
			Globals::setHasTexture(true);
			Globals::setUseTexture(_texId);
			Globals::setDiffuseColor(vec3(0,0,0));
		} else if(_texName != NULL) {
			Globals::setHasTexture(true);
			Globals::setUseTexture(_texName);
			Globals::setDiffuseColor(vec3(0,0,0));
		} else {
			Globals::setHasTexture(false);
			Globals::setUseTexture((GLuint)0);
			Globals::setDiffuseColor(_diffuseColor);
		}

		Globals::setAlpha(_alpha);

		if(_normalMapName!=NULL){
			Globals::setUseNormalMap(_normalMapName);
		}
		Globals::setNormalMapDepth(_normalMapDepth);

		vec3 origAmbLight=Globals::getAmbientColor();
		Globals::setAmbientLightColor(this->_highlightColor+origAmbLight);

		Globals::setModelTransMatrix(getTransformationMatrix());

		if(_modelName!=NULL)Globals::drawModel(_modelName);

		Globals::setAmbientLightColor(origAmbLight);

	}
	inline void setShininess(float f){_shininess=f;}
	inline void setTexture(char* t){useTexId=false;_texName=t;if(t=="")_texName=NULL;}
	inline void setTexture(GLuint id){useTexId=true;_texId=id;}
	inline void setNormalMap(char* t){_normalMapName=t;if(t=="")_normalMapName=NULL;else setNormalMapDepth(1.0);}
	inline void setNormalMapDepth(float f){_normalMapDepth=f;}

	inline void setAlpha(float a)
		{
			_alpha=a;
			if(a<1.0){setAlphaRequired(true);}
			else{setAlphaRequired(false);}
		}
	inline void setDiffuseColor(vec3 c){_diffuseColor=c;_texName=NULL;}
	inline void setDiffuseColor(vec4 c){setDiffuseColor(vec3(c.x,c.y,c.z));setAlpha(c.w);}
	inline void setDiffuseColor(float r, float g, float b, float a=1.0){setDiffuseColor(vec4(r,g,b,a));}
	
	inline void setHighlightColor(vec3 v){_highlightColor=v;}
	inline void setHighlightColor(float r, float g, float b){setHighlightColor(vec3(r,g,b));}

	inline void setModel(char* m){_modelName=m;if(m=="")_modelName=NULL;}
	inline void setUVOffset(float u, float v){_uvOffset=vec2(u,v);}
	inline void setUVScale(float u, float v){_uvScale=vec2(u,v);}

	inline void setAlphaRequired(bool t){_alphaFlag=t;}
	inline bool isAlphaRequired()const{return _alphaFlag;}

};

#endif