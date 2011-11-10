#ifndef _GAMEENTITY
#define _GAMEENTITY

#include "WorldEntity.h"
#include "CollisionBox.h"
#include "DrawableEntity.h"

//Potential IDs
class GameEntity:public WorldEntity{
private:
	CollisionBox _hitBox;

	DrawableEntity* _models[5];

	int _id;

	GameEntity();
public:
	GameEntity(int id);
	~GameEntity();

	int getId() const { return _id; }
	const CollisionBox& getHitBox() const { return _hitBox; }

	virtual void onCollide(GameEntity);
	bool setModel(const DrawableEntity& d, int num=0);

	virtual void update();
	virtual void draw() const;
};

#endif