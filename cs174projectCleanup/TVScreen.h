#ifndef TVSCREEN_H
#define TVSCREEN_H

#include "Framebuffer.h"
#include "CameraEntity.h"

struct TVCamera {
	Framebuffer framebuffer;
	CameraEntity cameraEntity;

	TVCamera() {} //Use default framebuffer size
	TVCamera(int width, int height) : framebuffer(width, height) {}
};

#include "GameEntity.h"

class TVScreen : public GameEntity {
public:
	TVScreen();

	void setFramebuffer(const Framebuffer& buf);
	void setTVCamera(const TVCamera& cam) {
		setFramebuffer(cam.framebuffer);
	}

	void update(){}
	void onCollide(const GameEntity&){}
};

#endif
