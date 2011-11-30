#ifndef TVSCREEN_H
#define TVSCREEN_H

#include "Framebuffer.h"
#include "CameraEntity.h"

/** A TVCamera consists of a framebuffer to record the camera's view and
  * a CameraEntity proper for positioning and transforming the camera.
  */
struct TVCamera {
	Framebuffer framebuffer;
	CameraEntity cameraEntity;

	/** Constructs a TVCamera with a default framebuffer size. */
	TVCamera() {}
	/** Constucts a TVCamera.
	  * @param width Default width.
	  * @param height Default height.
	  */
	TVCamera(int width, int height) : framebuffer(width, height) {}
};

#include "GameEntity.h"

/** A TVScreen, when paired with a TVCamera, is a box that displays
  * the camera's view on its faces.
  */
class TVScreen : public GameEntity {
public:
	/** Constructs a TVScreen, loading and preparing the tvcube model.
	  * @param id GameEntity id. Defaults to a normal wall.
	  */
	TVScreen(int id = ID_WALL);

	/** Set the framebuffer to use as a texture.
	  * Ideally, use a TVCamera and the corresponding
	  * setTVCamera() instead.
	  * @param buf Backing framebuffer.
	  */
	void setFramebuffer(const Framebuffer& buf);
	/** Set the camera whose frame to display.
	  * @param cam Backing TVCamera.
	  */
	void setTVCamera(const TVCamera& cam) {
		setFramebuffer(cam.framebuffer);
	}

	void update(){} ///< Nothing to update.
	void onCollide(const GameEntity&){} ///< Inert. Does nothing.
};

#endif
