#include "TVScreen.h"
#include "CollisionBox.h"

TVScreen::TVScreen() : GameEntity(ID_WALL) {
	setModel(DrawableEntity(NULL,"Resources/tvcube.obj"));
	DrawableEntity& model = getModel();
	model.setScale(1, 1, .01); //Make it thin, essentially on the XY plane

	setHitbox(CollisionBox(vec3(1,1,.01)));
}

void TVScreen::setFramebuffer(const Framebuffer& buf) {
	getModel().setTexture(buf.texture());
}