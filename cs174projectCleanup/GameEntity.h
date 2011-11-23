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
	ID_BULLET_CURVY,
	ID_EXPLOSION,
	ID_WANDERING_EMEMY,
	ID_SHIELD
};

/** @brief GameEntity is the parent class for everything
  * that is involved in the game from bullets to enemies
  * and includes the components to draw everything to screen
  * and for collision detection
  */

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

	/** @brief Returns whether or not the object is supposed to be deleted or not
	*/
	bool toDelete()const {
		return _delete;
	}

	/** @brief update is called every frame on every game entity
	* this is where animation, movement etc can be done */
	virtual void update()=0;

	virtual void draw() const;
};

#endif
