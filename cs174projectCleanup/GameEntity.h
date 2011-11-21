#ifndef _GAMEENTITY
#define _GAMEENTITY

#include "WorldEntity.h"
#include "CollisionBox.h"
#include "DrawableEntity.h"

enum GameEntityType {
	ID_PLAYER = 0,
	ID_ENEMY_TURRET,
	ID_WALL,
	ID_BULLET_STRAIGHT,
	ID_BULLET_GRENADE,
	ID_EXPLOSION,
	ID_SHIELD
};


//Potential IDs
class GameEntity:public WorldEntity{
public:
	static const int MAX_MODELS=5;
private:
	CollisionBox _hitBox;
	DrawableEntity* _models[MAX_MODELS];
	unsigned int _id;
	bool _delete;
protected:
	/** @brief Allows access to any DrawableEntity for animations
	*/
	DrawableEntity& getModel(int num=0) const;
	/** @brief Sets the delete flag so that Globals::animate() will delete this
	  *  object ASAP.
	  */
	void setDelete() { _delete = true; }
public:

	/** @brief Allows access to the CollisionBox of the GameEntity
	 */
	void setHitbox(const CollisionBox &cb);

	/** @brief Constructs a GameEntity with id id
	 */
	GameEntity(unsigned int id);
	~GameEntity();
	/** @brief Allows access to any DrawableEntity for read only
	*/
	inline const DrawableEntity& getModelConst(int num=0) const{return getModel(num);}

	/** @brief returns the id of the entity
	 */
	inline unsigned int getId() const { return _id; }
	/** @brief Allows access to the CollisionBox of the Entity
	 */
	inline const CollisionBox& getHitBox() const { return _hitBox; }

	/** @brief Returns true if the entities collided
	 */
	bool didCollide(const GameEntity&);
	/** @brief Should be overloaded to allow for specific behavior when hit
	 */
	virtual void onCollide(const GameEntity&)=0;
	/** @brief Allows for the ability to set the models of the entity
	 */
	bool setModel(const DrawableEntity& d, int num=0);
	/** @brief Allows for hte ability to remove any model from the entity
	 */
	bool removeModel(int num=0);

	bool toDelete()const {
		return _delete;
	}

	virtual void update()=0;
	virtual void draw() const;
};

#endif