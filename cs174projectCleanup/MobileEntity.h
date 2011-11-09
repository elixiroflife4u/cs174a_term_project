#ifndef _MOBILEENTITY
#define _MOBILEENTITY

#include "GameEntity.h"

class MobileEntity: public GameEntity{
private:
	vec3 _acc;
	vec3 _vel;

public:
	void setAcc(float x, float y, float z);
	void accelerate(float x, float y, float z);
	vec3 getAcc() const;

	void setVel(float x, float y, float z);
	void velocity (float x, float y, float z);
	vec3 getVel() const;

	virtual void update();
};



#endif //_MOBILEENTITY