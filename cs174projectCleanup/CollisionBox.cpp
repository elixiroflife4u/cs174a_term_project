#include "CollisionBox.h"

CollisionBox::CollisionBox()
	:_dimensions(vec3(1,1,1))
{}

bool CollisionBox::didCollide(const CollisionBox& b) const
{
	vec3 v1=b.getPoint1()-this->getPoint1();
	vec3 v2=b.getPoint2()-this->getPoint2();

	if((v1.x>=0)!=(v2.x>=0)){
		if((v1.y>=0)!=(v2.y>=0)){
			if((v1.z>=0)!=(v2.z>=0)){
				return true;
			}
		}
	}

	return false;
}

void CollisionBox::setDim(float x, float y, float z)
{
	//sets the dimensions of the box
	_dimensions.x=x;
	_dimensions.y=y;
	_dimensions.z=z;
}
void CollisionBox::setDim(vec3 d)
{
	//sets the dimensions of the box
	setDim((float)d.x, (float)d.y,(float)d.z);
}
void CollisionBox::setTranslate(float x,float y, float z)
{
	WorldEntity::setTranslate(x,y,z);
}
void CollisionBox::setTranslate(vec3 v)
{
	WorldEntity::setTranslate(v.x,v.y,v.z);
}

vec3 CollisionBox::getPoint1() const
{
	//get the positive side point
	return getTranslate()+_dimensions/2 ;
}
vec3 CollisionBox::getPoint2() const
{
	//get the negative side point
	return getTranslate()-_dimensions/2 ;
}

