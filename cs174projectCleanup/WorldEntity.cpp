#include "WorldEntity.h"

WorldEntity::WorldEntity(WorldEntity* parent)
{
	///@todo implement
}

//Translation
void WorldEntity::translate(vec3 v)
{
	///@todo implement
}
void WorldEntity::translate(float x, float y, float z)
{
	///@todo implement
}
void WorldEntity::setTranslate(float x, float y, float z)
{
	///@todo implement
}
void WorldEntity::setTranslateX(float x)
{
	///@todo implement
}
void WorldEntity::setTranslateY(float y)
{
	///@todo implement
}
void WorldEntity::setTranslateZ(float z)
{
	///@todo implement
}
vec3 WorldEntity::getTranslate() const
{
	///@todo implement
	return vec3();
}

//Rotation
void WorldEntity::rotate(float x, float y, float z)
{
	///@todo implement
}
void WorldEntity::setRotate(float x, float y, float z)
{
	///@todo implement
}
vec3 WorldEntity::getRotate() const
{
	///@todo implement
	return vec3();
}

//Scale
void WorldEntity::scale(float x, float y, float z)
{
	///@todo implement
}
void WorldEntity::setScale(float x, float y, float z)
{
	///@todo implement
}
vec3 WorldEntity::getScale() const
{
	///@todo implement
	return vec3();
}

//TransformationMatrix
mat4 WorldEntity::getTransformationMatrix() const
{
	///@todo implement
	return mat4();
}