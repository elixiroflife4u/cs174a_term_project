#ifndef _CAMERAENTITY
#define _CAMERAENTITY

#include "Angel.h"
#include "WorldEntity.h"
class CameraEntity:public WorldEntity{
private:
	float _fov;
	float _nearClip;
	float _farClip;
	float _aspect;
public:
	CameraEntity(float fov=75.00, float ar=1.00, float nc=1.00, float fc=500.00);

	void setFov(float);
	void setNearClip(float);
	void setFarClip(float);
	void setAspectRatio(float);

	Angel::mat4 getPerspectiveMatrix() const;
	Angel::mat4 getOrthographicMatrix() const;
};

#endif //_CAMERAENTITY