#ifndef _WORLDENTITY
#define _WORLDENTITY

#include "vec.h"
#include "mat.h"

class WorldEntity{
private:
	vec3 _position;
	vec3 _rotation;
	vec3 _scale;

	WorldEntity* _parent;

public:
	WorldEntity();

	//Translation
	void translate(vec3 v);
	void translate(float x, float y, float z);
	void setTranslate(float x, float y, float z);
	void setTranslateX(float x);
	void setTranslateY(float y);
	void setTranslateZ(float z);
	vec3 getTranslate() const;
	vec3 getLocalTranslate() const;

	//Rotation
	void rotate(float x, float y, float z);
	void setRotate(float x, float y, float z);
	vec3 getRotate() const;
	vec3 getLocalRotate() const;

	//Scale
	void scale(float x, float y, float z);
	void setScale(float x, float y, float z);
	vec3 getScale() const;
	vec3 getLocalScale()const;

	//Parent
	WorldEntity* getParent() const;

	//TransformationMatrix
	mat4 getTransformationMatrix() const;
};


#endif //_WORLDENTITY