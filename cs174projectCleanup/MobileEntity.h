#ifndef _MOBILEENTITY
#define _MOBILEENTITY

#include "GameEntity.h"

/** @brief This abstract class provides motion for GameEntity objects. */
class MobileEntity: public GameEntity{
private:
	vec3 _acc; ///< The current acceleration.
	vec3 _vel; ///< The current velocity.

public:
	/** @brief Sets the acceleration, discarding the current value. */
	void setAcc(float x, float y, float z) { _acc = vec3(x, y, z); }
	/** @brief Adds a new acceleration vector to the current one. */
	void accelerate(float x, float y, float z) { _acc += vec3(x, y, z); }
	/** @brief Returns the current acceleration. */
	vec3 getAcc() const { return _acc; }
	
	/** @brief Sets the velocity, discarding the current value. */
	void setVel(float x, float y, float z) { _vel = vec3(x, y, z); }
	/** @brief Adds a new velocity vector to the current one. */
	void velocity (float x, float y, float z) { _vel += vec3(x, y, z); }
	/** @brief Returns the current velocity. */
	vec3 getVel() const { return _vel; }
	
	/** @brief Updates the state of the object every frame. 
	  * Must be provided by subclasses. */
	virtual void update() = 0;
};



#endif //_MOBILEENTITY