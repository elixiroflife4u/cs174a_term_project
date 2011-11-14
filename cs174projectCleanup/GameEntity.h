#ifndef _GAMEENTITY
#define _GAMEENTITY

#include "WorldEntity.h"
#include "CollisionBox.h"
#include "DrawableEntity.h"

const unsigned int ID_PLAYER=0;
const unsigned int ID_WALL=1;



//Potential IDs
class GameEntity:public WorldEntity{
private:
	CollisionBox _hitBox;
	DrawableEntity* _models[5];
	unsigned int _id;
protected:
	/** @brief Allows access to the CollisionBox of the GameEntity
	 */
	void setHitbox(const CollisionBox &cb);
	/** @brief Allows access to any DrawableEntity for animations
	*/
	DrawableEntity* getModel(int num=0);
public:
	/** @brief Constructs a GameEntity with id id
	 */
	GameEntity(unsigned int id);
	~GameEntity();

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

	virtual void update()=0;
	virtual void draw() const;
};

#endif