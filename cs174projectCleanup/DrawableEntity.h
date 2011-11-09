#ifndef _DRAWABLEENTITY
#define _DRAWABLEENTITY

#include "WorldEntity.h"

class DrawableEntity:public WorldEntity{
private:
	char* _textureName;
	char* _modelName;
public:
	DrawableEntity(char* mName, char* tName);
	DrawableEntity(char* mName);

	void setModel(char* mName);
	void setTexture(char* tName);
	void draw() const;
};

#endif