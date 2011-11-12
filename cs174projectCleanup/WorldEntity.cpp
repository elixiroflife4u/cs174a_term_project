#include "WorldEntity.h"

WorldEntity::WorldEntity(WorldEntity* parent)
{
	_parent = parent;
	_position = vec3(0, 0, 0);
	_rotation = vec3(0, 0, 0);
	_scale    = vec3(0, 0, 0);
}

//Translation
void WorldEntity::translate(vec3 v)
{
	_position = _position + v;
}

void WorldEntity::translate(float x, float y, float z)
{
	_position = _position + vec3(x, y, z);
}

void WorldEntity::setTranslate(float x, float y, float z)
{
	_position = vec3(x, y, z);	
}

void WorldEntity::setTranslateX(float x)
{
	_position = vec3(x, 0, 0);
}
void WorldEntity::setTranslateY(float y)
{
	_position = vec3(0, y, 0);
}
void WorldEntity::setTranslateZ(float z)
{
	_position = vec3(0, 0, z);
}
vec3 WorldEntity::getTranslate() const
{
	vec3 t;
	if (_parent == NULL)
		t = _position;
	else
		t = _parent->getTranslate() + _position;
	
	return t;
}



//Rotation
void WorldEntity::rotate(float x, float y, float z)
{
	_rotation = _rotation + vec3(x, y, z);
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
	_scale = _scale + vec3(x, y, z);
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
		s = _parent->getScale() + _scale;
	
	return s;
}


//TransformationMatrix
mat4 WorldEntity::getTransformationMatrix() const
{
	mat4 m = Angel::Translate(_position.x, _position.y, _position.z) * RotateX(_rotation.x) * RotateY(_rotation.y) * RotateZ(_rotation.z);
	if(_parent == NULL)
		return m;

	else
		return _parent->getTransformationMatrix() * m;
}