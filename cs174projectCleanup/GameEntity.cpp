#include "GameEntity.h"

GameEntity::GameEntity(unsigned int id)
	:_id(id),_delete(false)
{
	//sets the drawableEntity pointers to null to start
	for(int i=0;i<5;i++){
		_models[i]=NULL;
	}
	_hitBox.setParent(this);
}
GameEntity::~GameEntity()
{
	//delete all of the drawableEntities defined for the entity
	for(int i=0;i<5;i++){
		if(_models[i]!=NULL){
			delete _models[i];
		}
	}
}

void GameEntity::setHitbox(const CollisionBox &cb){
	//sets the hitbox to the one that is passed
	_hitBox=cb;
	_hitBox.setParent(this);
}
bool GameEntity::didCollide(const GameEntity& g)
{
	//checks if the gamentity collided with the current one
	return getHitBox().didCollide(g.getHitBox());
}
void GameEntity::onCollide(const GameEntity& g)
{}
bool GameEntity::setModel(const DrawableEntity& d, int num)
{
	//sets the indicated model num to be 'd' if num is valid
	//returns true if model was successfully added, false otherwise
	if(num<0||num>=5){
		return false;
	}
	_models[num]=new DrawableEntity(d);
	_models[num]->setParent(this);
	return true;
}
bool GameEntity::removeModel(int num){
	//removes the indicated model num from _models
	//returns true if the model was successfully removed, false otherwise
	if(num<0||num>=5||_models[num]==NULL){
		return false;
	}
	delete _models[num];
	_models[num]=NULL;
	return true;
}
DrawableEntity& GameEntity::getModel(int num) const
{
	//returns a pointer to the indicated model so it maybe be modified for animations
	if(num<0||num>=5){
		throw new CException("Array out of bound");
	}
	return *_models[num];
}

void GameEntity::update()
{}
void GameEntity::draw() const
{
	//Draws every model associated with the entity
	for(int i=0;i<5;i++){
		if(_models[i]!=NULL)_models[i]->draw();
	}
}