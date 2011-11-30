#include "Teleporter.h"
#include "General.h"
#include "MobileEntity.h"
#include <algorithm>
#include <cmath>

Teleporter::Teleporter() : TVScreen(ID_TELEPORTER), _camera(new TVCamera), _pair(NULL) {
	Globals::addTVCamera(_camera);
	_camera->cameraEntity.setParent(this);
	//Push camera to outside of TVScreen
	_camera->cameraEntity.translate(0, -3, -1);
	_camera->cameraEntity.setFov(45);
}


Teleporter::~Teleporter() {
	//Unpair if applicable
	if(_pair)
		_pair->_pair = NULL;

	//Delete associated camera, if applicable
	Globals::TVCameraList::iterator i = std::find(Globals::wTVCameras.begin(), Globals::wTVCameras.end(), _camera);
	if(i != Globals::wTVCameras.end())
		Globals::deleteTVCamera(i);
}

const float Teleporter::SITE_OFFSET = 8;
vec3 Teleporter::teleportSite() const {
	const Teleporter* other = _pair ? _pair : this;

	const vec4 offset = RotateY(other->getRotate().y) * vec4(0,0,-SITE_OFFSET,0);
	return other->getTranslate() + *reinterpret_cast<const vec3*>(&offset);
}

void Teleporter::teleport(MobileEntity* e) const {
	if(paired()) {
		e->setTranslate(teleportSite());
		e->setVel(0,0,0);
		e->setAcc(0,0,0);
	}
}

void Teleporter::update() {
	if(!_pair) return;

	//Calculate teleporter pair rotation offset
	const float curY = getRotate().y;
	const float pairY =  _pair->getRotate().y;
	const float yDiff = pairY - curY;

	//Calculate view vector
	const Player* const player = Globals::getPlayer();
		//Subtract vec3(0,.25,0) * getScale().y to make reference point at bottom
		//of screen, where the player most likely is.
	vec4 view = getTranslate() - player->getTranslate() - vec3(0,.25,0) * getScale().y;
	view.w = 0;
	view = normalize(view);

	//The "reflection" vector is really just
	//a continuation of the view vector past the plane,
	//as if we were looking through it. We also have
	//to take into consideration the difference between
	//each teleporter's orientation.
	const vec4 pairCamera = RotateY(yDiff) * (-view);

	//Set pair camera's view to match our view vector
	const float yaw = std::atan2(-pairCamera.z, pairCamera.x);
	const float pitch = std::atan2(pairCamera.y, std::sqrt((pairCamera.x * pairCamera.x) + (pairCamera.z * pairCamera.z)));
	//We have to subtract curY to take into consideration that we calculated the global rotation,
	//but we can only set the local rotation. We'll subtract curY, which will get added
	//back later when the global rotation is calculated.
	//Also, we have to add 90 degrees because the the above equations use +x as 0 degrees,
	//but we use the normal (locally the -z axis) as 0 degrees.
	_pair->_camera->cameraEntity.setRotate(pitch / DegreesToRadians, yaw / DegreesToRadians + 90 - curY, 0);
}

void Teleporter::unpair() {
	if(_pair) {
		_pair->_pair = NULL;
		_pair = NULL;
	}
}

void Teleporter::setPair(Teleporter* a, Teleporter* b) {
	//If a or b already have a pair, unset the pair relationship.
	if(a->_pair)
		a->_pair->_pair = NULL;
	if(b->_pair)
		b->_pair->_pair = NULL;

	a->setTVCamera(*b->_camera);
	b->setTVCamera(*a->_camera);

	//Set pair pointers
	a->_pair = b;
	b->_pair = a;
}
