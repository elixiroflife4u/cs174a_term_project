#ifndef _MOBILEENTITY
#define _MOBILEENTITY

#include "GameEntity.h"

/** @brief This class provides motion for GameEntity objects. */
class MobileEntity: public GameEntity{
private:
	vec3 _acc; ///< The current acceleration.
	vec3 _vel; ///< The current velocity.

public:
	/** @brief Sets the acceleration, discarding the current value. */
	void setAcc(float x, float y, float z);
	/** @brief Adds a new acceleration vector to the current one. */
	void accelerate(float x, float y, float z);
	/** @brief Returns the current acceleration. */
	vec3 getAcc() const;
	
	/** @brief Sets the velocity, discarding the current value. */
	void setVel(float x, float y, float z);
	/** @brief Adds a new velocity vector to the current one. */
	void velocity (float x, float y, float z);
	/** @brief Returns the current velocity. */
	vec3 getVel() const;
	
	/** @brief Updates the state of the object every frame.
	 *  For example, MobileEntity moves the object every frame
	 *  based on its current acceleration and velocity.
	 * 
	 *  Subclasses should call the parent implementation
	 *  if they override this function.
	 */
	virtual void update();
};



#endif //_MOBILEENTITY