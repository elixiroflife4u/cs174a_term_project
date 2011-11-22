#ifndef guard_curvybulletentity_h
#define guard_curvybulletentity_h
#include "BulletEntity.h"
#include "Quaternion.h"

/** The CurvyBulletEntity is a bullet that travel in a flight curve
  * in the shape of a spiral.
  */
class CurvyBulletEntity: public BulletEntity
{
private:
	vec3 dir, ///< Current direction.
		 pos; ///< Current position.
	float velocityMag; ///< Speed.
	float radius; ///< Radius of the flight curve.
	Quaternion rotation; ///< Current rotation with respect to flight curve.
public:
	/** @brief Constructs a new CuvryBulletEntity.
	* @param posI Initial position.
	* @param dirI Initial direction.
	* @param velocityMagI Initial speed.
	*/
	CurvyBulletEntity(vec3 posI, vec3 dirI, float velocityMagI)
		: BulletEntity(posI, 10, ID_BULLET_CURVY), dir(dirI), pos(posI), velocityMag(velocityMagI), radius(1.f)
	{
		//MobileEntity::setVel(normalize(dir)*velocityMag);

		setModel(DrawableEntity(NULL,"Resources/grenade.obj"));
		scale(.75f,.75f,.75f);
		getModel().setDiffuseColor(0.9f,0.3f,0.4f);
		getModel().scale(.75f,.75f,.75f);
		getModel().setShininess(60);
		getModel().setHighlightColor(.25f,.7f,.2f);
		this->setHitbox(CollisionBox(vec3(1.5f,1.5f,1.5f)));
		rotation.FromAxis(dir, DegreesToRadians*1);
	}
	~CurvyBulletEntity()
	{
		//std::cout<<"curvy destoyed"<<std::endl;
	}
	void update()
	{
		pos += normalize(dir)*velocityMag;
		///HACK: for now, use 0,0,1. prolly shoud change to camera vec so that cross doesn't return a 0 vector
		vec3 perpToMotion = normalize(cross(vec3(0,0,1), dir));
		
		Quaternion localRot;
		localRot.FromAxis(dir, DegreesToRadians*30);
		localRot.normalise();
		rotation = localRot*rotation;
		rotation.normalise();
		vec3 vectorToNewPoint = normalize((rotation.getMatrix()*vec4(perpToMotion, 0)).Vec4ToVec3());
		WorldEntity::setTranslate(pos + radius*vectorToNewPoint);
		
		//problems: hit detection box?? 
		//perhaps should use collisionbox settranslate??


		//vec3 printAxis;
		//float printAngle;
		//rotation.getAxisAngle(printAxis, printAngle);
		//std::cout<<printAxis.x<<printAxis.y<<printAxis.z<<printAngle<<std::endl;

		//MobileEntity::setVel(MobileEntity::getAcc()+MobileEntity::getVel());
		//WorldEntity::translate(MobileEntity::getVel());
		//vec3 dir=Globals::getPlayer()->getTranslate()-getTranslate();
		vec3 dis=Globals::getPlayer()->getTranslate()-getTranslate();
		if(dot(dis,dis)>pow(300.0,2)){
			setDelete();
		}

	}
	void onCollide(const GameEntity& g)
	{
		//std::cout<<this<<std::endl<<"COLLIDED CURVY"<<std::endl;
		setDelete();
	}
};
#endif