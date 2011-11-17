#ifndef _MOBILEENTITY
#define _MOBILEENTITY

#include "GameEntity.h"

/** @brief This abstract class provides motion for GameEntity objects. */
class MobileEntity: public GameEntity{
private:
	vec3 _acc; ///< The current acceleration.
	vec3 _vel; ///< The current velocity.
	int _jumpCount;
	bool _delete;
	float _health;

public:
	MobileEntity(unsigned int id)
		:GameEntity(id),_jumpCount(0),_delete(false),_health(100)
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
	virtual void onCollide(const GameEntity& g)=0;
	void placeAtEdge(const GameEntity& g);
	void jump(float force=1.0);
	bool toDelete()const {
		return _delete;
	}

	float getHealth() const{
		return _health;
	}
	bool isAlive() const{
		if(_health>0){
			return true;
		}else{
			return false;
		}
	}
};



#endif //_MOBILEENTITY