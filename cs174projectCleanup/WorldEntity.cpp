#include "WorldEntity.h"
#include "Engine.h"

WorldEntity::WorldEntity(const WorldEntity* parent)
{
	_parent = parent;
	_position = vec3(0, 0, 0);
	_rotation = vec3(0, 0, 0);
	_scale    = vec3(1, 1, 1);
	_positionFrameCount = 0;
}

//Translation
void WorldEntity::translate(vec3 v)
{
	_position += v;
}

void WorldEntity::translate(float x, float y, float z)
{
	_position += vec3(x, y, z);
}

void WorldEntity::setTranslate(float x, float y, float z)
{
	_position = vec3(x, y, z);	
}
void WorldEntity::setTranslate(vec3 v){
	_position=v;
}

void WorldEntity::setTranslateX(float x)
{
	_position.x=x;
}
void WorldEntity::setTranslateY(float y)
{
	_position.y=y;
}
void WorldEntity::setTranslateZ(float z)
{
	_position.z = z;
}
vec3 WorldEntity::getTranslate() const
{
	if(Globals::frameCount != _positionFrameCount) {
		_positionFrameCount = Globals::frameCount;

		if (_parent == NULL){
			_worldPosition = _position;
		}else{
			vec4 temp = _parent->getTransformationMatrix()*vec4(_position,1.0);
			_worldPosition=vec3(temp.x,temp.y,temp.z);
		}
	}
	return _worldPosition;
}



//Rotation
void WorldEntity::rotate(float x, float y, float z)
{
	_rotation += vec3(x, y, z);
}
void WorldEntity::setRotate(float x, float y, float z)
{
	_rotation = vec3(x, y, z);
}
vec3 WorldEntity::getRotate() const
{
	vec3 r;
	if (_parent == NULL)
		r = _rotation;
	else
		r = _parent->getRotate() + _rotation;
	
	return r;
}


//Scale
void WorldEntity::scale(float x, float y, float z)
{
	_scale.x*=x;
	_scale.y*=y;
	_scale.z*=z;
}
void WorldEntity::setScale(float x, float y, float z)
{
	_scale = vec3(x, y, z);
}
vec3 WorldEntity::getScale() const
{
	vec3 s;
	if (_parent == NULL)
		s = _scale;
	else
		s = vec3(_parent->getScale().x*_scale.x,_parent->getScale().y*_scale.y,_parent->getScale().z*_scale.z);
	
	return s;
}


//TransformationMatrix
mat4 WorldEntity::getTransformationMatrix() const
{

	mat4 scaleMat=mat4();
	scaleMat[0][0]=_scale.x;
	scaleMat[1][1]=_scale.y;
	scaleMat[2][2]=_scale.z;
	scaleMat[3][3]=1;

	mat4 m = Translate(_position.x, _position.y, _position.z) * RotateX(_rotation.x) * RotateY(_rotation.y) * RotateZ(_rotation.z) * scaleMat;

	if(_parent == NULL)
		return m;
	else
		return _parent->getTransformationMatrix() * m;
}

mat4 WorldEntity::getCameraTransformationMatrix() const{
	mat4 m = RotateX(-_rotation.x) * RotateY(-_rotation.y) * RotateZ(-_rotation.z)*Translate(-_position.x, -_position.y, -_position.z) ;

	if(_parent == NULL)
		return m;
	else
		return  m * _parent->getCameraTransformationMatrix();
}