#ifndef guard_quaternion
#define guard_quaternion
#include "GlobalIncludes.h"

class Quaternion
{
public:
	Quaternion():TOLERANCE(0.00001f), x(0), y(0), z(0), w(1){}
	Quaternion(float xi, float yi, float zi, float wi): x(xi), y(yi), z(zi), w(wi), TOLERANCE(0.00001f) { }
	
	Quaternion getConjugate(){ return Quaternion(-x, -y, -z, w); }

	void normalise();
	/** @brief Multiplying q1 with q2 applies the rotation q2 to q1
	*/
	Quaternion operator* (const Quaternion &rq) const;
	Quaternion& Quaternion::operator=(const Quaternion &q)
	{
		x = q.x;
		y = q.y;
		z = q.z;
		w = q.w;

		return(*this);
	}	
	/** @brief Multiplying a quaternion q with a vector v applies the q-rotation to v
	*/
	vec3 operator* (const vec3 &vec) const;

	/** @brief Convert from Axis Angle to quaternion
	*/
	void Quaternion::FromAxis(const vec3 &v, float angle);
	
	/** @brief Generate and return a local quaternion based on the vector to rotate about and angle to rotate by
	*/
	Quaternion Quaternion::getLocalQuaternion(const vec3 &v, float angle);

	/**@bried Convert to Axis/Angles
	*/
	void Quaternion::getAxisAngle(vec3& axis, float& angle);

	/** @brief Convert quaternion to Matrix
	*/
	mat4 Quaternion::getMatrix() const;


private:
	float x,y,z,w;
	float TOLERANCE;

};


#endif