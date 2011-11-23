#include "Framebuffer.h"

Framebuffer::Framebuffer(int width, int height) : _width(width), _height(height) {
	//Initialize objects
	glGenFramebuffers(1, &_framebuffer);
	glGenTextures(1, &_texture);
	glGenRenderbuffers(1, &_zBuffer);
}

Framebuffer::~Framebuffer() {
	glDeleteRenderbuffers(1, &_zBuffer);
	glDeleteTextures(1, &_texture);
	glDeleteFramebuffers(1, &_framebuffer);
}

void Framebuffer::render(RenderFunc renderFunc, int width, int height) {
	//Save the original viewport so we can restore it in the end
	GLint origViewport[4];
	glGetIntegerv(GL_VIEWPORT, origViewport);

	glViewport(0,0,width,height);

	//Bind framebuffer and texture
	glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
	glBindTexture(GL_TEXTURE_2D, _texture);

	//Define and reset texture
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

	//Create new Z buffer
	glBindRenderbuffer(GL_RENDERBUFFER, _zBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _zBuffer);

	//Attach texture to frame buffer object
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, _zBuffer, 0);

	//Render stuff as normal
	renderFunc();

	//Configure texture and generate mipmap
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); 
	glGenerateMipmap(GL_TEXTURE_2D);

	//Unbind framebuffer and render buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	//Reset viewport
	glViewport(origViewport[0], origViewport[1], origViewport[2], origViewport[3]);
}