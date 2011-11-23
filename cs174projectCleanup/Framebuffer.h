#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "Angel.h"

/** The Framebuffer object enables capturing a render into a texture.
  * The texture can then be used for a couple of reasons, primarily for
  * rendering a screen or mirror in the world or saving the screen to
  * disk.
  */
class Framebuffer {
public:
	/** Type of render function that is used to render the world to the texture.
	  * Void return; no parameters.
	  */
	typedef void(*RenderFunc)(void);

	/** Constructs a new Framebuffer, allocating a framebuffer, texture, and depth
	  * map specifically for it.
	  */
	Framebuffer();
	/** Destroys a Framebuffer, deallocating its framebuffer, texture, and depth map. */
	~Framebuffer();
	/** Renders a scene into the texture.
	  * @param renderFunc Pointer to render function which executes all commands to render
	  *   the scene.
	  * @param width The width of the viewport.
	  * @param height The height of the viewport.
	  */
	void render(RenderFunc renderFunc, int width = 320, int height = 320);

	/** Returns the texture handle for this framebuffer. */
	GLuint texture() const { return _texture; }

private:
	Framebuffer(const Framebuffer&);
	Framebuffer& operator=(const Framebuffer&);

	GLuint _framebuffer; ///< Framebuffer handle
	GLuint _texture; ///< Texture handle
	GLuint _zBuffer; ///< Depth buffer handle
};

#endif