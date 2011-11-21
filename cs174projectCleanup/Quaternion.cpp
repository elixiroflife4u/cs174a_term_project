#include "Quaternion.h"
void Quaternion::normalise()
{
	// Don't normalize if we don't have to
	float mag2 = w * w + x * x + y * y + z * z;
	if (fabs(mag2) > TOLERANCE && fabs(mag2 - 1.0f) > TOLERANCE) {
		float mag = sqrt(mag2);
		w /= mag;
		x /= mag;
		y /= mag;
		z /= mag;
	}
}

Quaternion Quaternion::operator* (const Quaternion &rq) const
{
	// the constructor takes its arguments as (x, y, z, w) equations are for unit quaternian
	return Quaternion(w * rq.x + x * rq.w + y * rq.z - z * rq.y,
	                  w * rq.y + y * rq.w + z * rq.x - x * rq.z,
	                  w * rq.z + z * rq.w + x * rq.y - y * rq.x,
	                  w * rq.w - x * rq.x - y * rq.y - z * rq.z);
}

vec3 Quaternion::operator* (const vec3 &vec) const
{
	vec3 vn = Angel::normalize(vec);
	
	Quaternion vecQuat(vn.x, vn.y, vn.z, 0.0f), resQuat;
	//vecQuat.x = vn.x;
	//vecQuat.y = vn.y;
	//vecQuat.z = vn.z;
	//vecQuat.w = 0.0f;
	Quaternion conjQ = Quaternion(-x, -y, -z, w);
 
	resQuat = vecQuat * conjQ;
	resQuat = *this * resQuat;
 
	return (vec3(resQuat.x, resQuat.y, resQuat.z));
}

// Convert from Axis Angle
void Quaternion::FromAxis(const vec3 &v, float angle) //v is the normalized axis, angle is in radians
{
	if(!v.x && !v.y && !v.z){
		x = 0;
		y = 0;
		z = 0;
		w = 1;
		return;
	}

	float sinAngle;
	angle *= 0.5f;
	vec3 vn = normalize(v);
	 
	sinAngle = sin(angle);
 
	x = (vn.x * sinAngle);
	y = (vn.y * sinAngle);
	z = (vn.z * sinAngle);
	w = cos(angle);
}

Quaternion Quaternion::getLocalQuaternion(const vec3 &v, float angle) //v is the axis
{
	float sinAngle;
	angle *= 0.5f;
	vec3 vn = normalize(v);
	 
	sinAngle = sin(angle);
	Quaternion ret = Quaternion(vn.x * sinAngle, vn.y * sinAngle, vn.z * sinAngle,  cos(angle));
	ret.normalise(); //not sure if normalization of this quat is required or not.
 
	return ret;
}

// Convert to Axis/Angles
void Quaternion::getAxisAngle(vec3& axis, float& angle)
{
	float scale = sqrt(x * x + y * y + z * z);
	axis.x = x / scale;
	axis.y = y / scale;
	axis.z = z / scale;
	angle = acos(w) * 2.0f;
}
////todo fix this if needed.
mat4 Quaternion::getMatrix() const
{
	float x2 = x * x;
	float y2 = y * y;
	float z2 = z * z;
	float xy = x * y;
	float xz = x * z;
	float yz = y * z;
	float wx = w * x;
	float wy = w * y;
	float wz = w * z;
 
	//there seems to be contraditing version for this matrix at these two loc
	//http://content.gpwiki.org/index.php/OpenGL:Tutorials:Using_Quaternions_to_represent_rotation
	//http://www.cprogramming.com/tutorial/3d/quaternions.html
	//the book seems to be supporting first link (atleast based on the patern of things)
	// i am using the first one. link also useful http://www.gamedev.net/page/resources/_/technical/math-and-physics/quaternion-powers-r1095
	vec4 v1(1.0f - 2.0f * (y2 + z2), 2.0f * (xy - wz)       , 2.0f * (xz + wy)       , 0.0f);
	vec4 v2(2.0f * (xy + wz)       , 1.0f - 2.0f * (x2 + z2), 2.0f * (yz - wx)       , 0.0f);
	vec4 v3(2.0f * (xz - wy)       , 2.0f * (yz + wx)       , 1.0f - 2.0f * (x2 + y2), 0.0f);
	vec4 v4(0.0f                   , 0.0f                   , 0.0f                   , 1.0f);
	
	return mat4( v1, v2, v3, v4	); 
}