#ifndef WANDERING_ENEMY_H
#define WANDERING_ENEMY_H

#include "MobileEntity.h"

/** The WanderingEnemy is an enemy that wanders around the map randomly
  * but can lock on to the player if he enters within its field of view
  * and a maximal distance. When locked on, the enemy attempts to face
  * the player (but can only rotate a maximal number of degrees each
  * frame, so the movement is smooth and not instantaneous). If the player
  * is farther than a minimal distance, the enemy also moves in the direction
  * of the player. Finally, while locked on, the enemy fires a bullet in its
  * current direction (which may not be the direction of the player, given the aforementioned
  * rotational behavior). The firing rate is limited.
  */
class WanderingEnemy : public MobileEntity {
private:
	int _wanderCount; ///< Number of frames remanining until the next direction is decided.
	int _bulletDelay; ///< Number of frames remaining until the enemy can fire a bullet.
	double _desiredHeading; ///< Desired wander heading in degrees

	static const int WANDER_COUNT = 60; ///< Number of frames between deciding the wander direction.
	static const int BULLET_DELAY = 5; ///< Number of frames between firing bullets.
	static const double FOV, ///< The entities field of view in the XZ plane (infitine elsewhere).
	                    MIN_DISTANCE, ///< If closer to player than this, it will fire but not translate.
	                    MAX_DISTANCE, ///< If farther from player than this, it will ignore the player.
						MAX_ROTATE; ///< The maximal rotation in degrees per frame.

	/** Makes the enemy wander for the next frame.
	  * If _wanderCount is non-zero, it simply decrements the count.
	  * If it is zero, it chooses a random direction as the next
	  * _desiredHeading, sets the accleration so as to move
	  * towards it, and resets the count.
	  */
	void wander();
	/** Makes the enemy target the player. Called when the player is
	  * within sight (within FOV and closer than MAX_DISTANCE).
	  * If the player is farther than MIN_DISTANCE, sets the accleration
	  * so as to move towards the player; otherwise, it halts the enemy.
	  * Sets the desired heading as towards the player.
	  * If _bulletDelay is zero, fires a bullet in the positive X direction
	  * and resets
	  * count; otherwise decrements count.
	  * @param xz The absolute heading towards the player (0 is east) in radians.
	  * @param distance The distance to the player.
	  * @param currentXZ The current heading of the enemy.
	  */
	void lockOnPlayer(double xz, double distance, double currentXZ);
public:
	/** Constructs a new enemy.
	  * @pos The enemy's global position.
	  */
	WanderingEnemy(vec3 pos = vec3(0,0,0));

	/** Updates the enemy each frame.
	  * Determines if enemy should be in wander mode or lock-on mode
	  * and calls the correct function. Actuates gravity, desired
	  * acceleration, and desired heading. Deletes on death and resets
	  * the hit highlight.
	  */
	void update();
	/** Handles a collision.
	  * Decrements health if bullet or explosion.
	  * If wall, enemy, or player, places at edge.
	  * @param g The object with which the enemy collided.
	  */
	void onCollide(const GameEntity& g);
};

#endif