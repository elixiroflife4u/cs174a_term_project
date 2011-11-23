#ifndef _MOBILEENTITY
#define _MOBILEENTITY
#include "GameEntity.h"

/** @brief This abstract class provides motion for GameEntity objects. */
class MobileEntity: public GameEntity{
private:
	vec3 _acc; ///< The current acceleration.
	vec3 _vel; ///< The current velocity.
	int _jumpCount;
	float _health;
protected:
	/** @brief decreases the entity's health by the passed amount and
	* sets the highlight to red to indicate damage
	*/
	void decHealth(float f){
		_health-=f;

		if(f<=0)return;

		for(int i=0;i<MAX_MODELS;i++){
			if((&getModel(i))!=NULL)
				getModel(i).setHighlightColor(1,.1,.1);
		}
	}
	/** @brief resets the drawableobjects to use no highlight
	* should be recalled every time the highlight needs to be reset
	* like every frame
	*/
	void resetHightlight(){
		for(int i=0;i<MAX_MODELS;i++){
			if((&getModel(i))!=NULL)
				getModel(i).setHighlightColor(0,0,0);
		}
	}
	void setHealth(float f){
		_health=f;
	}
public:
	MobileEntity(unsigned int id, float health=100)
		:GameEntity(id),_jumpCount(0),_health(health)
	{}
	/** @brief Sets the acceleration, discarding the current value. */
	void setAcc(float x, float y, float z) { _acc = vec3(x, y, z); }
	void setAcc(vec3 v){setAcc(v.x,v.y,v.z);}
	void setAccX(float x){_acc.x=x;}
	void setAccY(float y){_acc.y=y;}
	void setAccZ(float z){_acc.z=z;}
	/** @brief Adds a new acceleration vector to the current one. */
	void increaseAcc(float x, float y, float z) { _acc += vec3(x, y, z); }
	void increaseAcc(vec3 v){ increaseAcc(v.x,v.y,v.z);}
	/** @brief Returns the current acceleration. */
	vec3 getAcc() const { return _acc; }
	
	/** @brief Sets the velocity, discarding the current value. */
	void setVel(float x, float y, float z) { _vel = vec3(x, y, z); }
	void setVel(vec3 v){setVel(v.x,v.y,v.z);}
	void setVelX(float x){_vel.x=x;}
	void setVelY(float y){_vel.y=y;}
	void setVelZ(float z){_vel.z=z;}
	/** @brief Adds a new velocity vector to the current one. */
	void increaseVel (float x, float y, float z) { _vel += vec3(x, y, z); }
	void increaseVel (vec3 v){increaseVel(v.x,v.y,v.z);}
	/** @brief Returns the current velocity. */
	vec3 getVel() const { return _vel; }
	
	/** @brief Updates the state of the object every frame. 
	  * Must be provided by subclasses. */
	virtual void update(){
		increaseVel(getAcc());
		translate(getVel());
	}
	/** @brief dictates what is to be done when it collides with another
	* gameEntity
	*/
	virtual void onCollide(const GameEntity& g)=0;
	/** @brief places the entity at the edge of the passed
	* GameEntity's hit box at a reasonable location
	*/
	virtual void placeAtEdge(const GameEntity& g);
	void jump(float force=1.0);

	/** @brief returns the health of the entity */
	float getHealth() const{
		return _health;
	}
	/** @brief returns whether or not the entity is alive or not */
	bool isAlive() const{
		if(_health>0){
			return true;
		}else{
			return false;
		}
	}
};



#endif //_MOBILEENTITY