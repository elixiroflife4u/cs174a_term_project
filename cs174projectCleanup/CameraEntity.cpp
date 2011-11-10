#include "CameraEntity.h"

CameraEntity::CameraEntity(float fov, float ar, float nc, float fc)
	:_fov(fov),_aspect(ar),_nearClip(nc),_farClip(fc)
{}
Angel::mat4 CameraEntity::getPerspectiveMatrix() const{
	return Angel::Perspective(_fov,_aspect,_nearClip,_farClip);
}
void CameraEntity::setFarClip(float fc){
	this->_farClip=fc;
}
void CameraEntity::setNearClip(float nc){
	this->_nearClip=nc;
}
void CameraEntity::setFov(float fov){
	this->_fov=fov;
}
void CameraEntity::setAspectRatio(float ar){
	_aspect=ar;
}
mat4 CameraEntity::getReverseTransformationMatrix() const{
	return mat4();
}