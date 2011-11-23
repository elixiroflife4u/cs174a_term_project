#ifndef _CAMERAENTITY
#define _CAMERAENTITY

#include "Angel.h"
#include "WorldEntity.h"

/** This class represents a render camera and provides the corresponding
  * camera transformation, for both perspective and orthographic projections.
  * It is parameterized around the field of view, depth of the clipping planes,
  * and aspect ratio.
  *
  * As a WorldEntity, the camera may be translated and rotated away from the origin.
  * However, note that getPerspectiveMatrix() and getOrthographicMatrix() do not
  * return the transformation necessary to acutate translation and rotation of the
  * camera. Instead, the inverse transformation -- provided by
  * WorldEntity::getCameraTransformationMatrix() -- must be applied first to
  * shift the world into the camera's frustrum.
  */
class CameraEntity:public WorldEntity{
private:
	float _fov; ///< Field of view in degrees.
	float _nearClip; ///< Depth of the near clipping plane.
	float _farClip; ///< Depth of the far clipping plane.
	float _aspect; ///< Aspect ratio (width to height).
public:
	/** Constructs a new CameraEntity
	  * @param fov Field of view in degree.
	  * @param ar Aspect ratio.
	  * @param nc Depth of near clipping plane.
	  * @param fc Depth of the far clipping plane.
	  */
	CameraEntity(float fov=75.00, float ar=1.00, float nc=1.00, float fc=500.00);

	void setFov(float); ///< Set the field of view in degrees.
	void setNearClip(float); ///< Set the near clipping plane.
	void setFarClip(float); ///< Set the far clipping plane.
	void setAspectRatio(float); ///< Set the aspect ratio.

	/** Gets the aspect ratio. */
	float getAspectRatio() const  { return _aspect; }

	/** Returns the perspective projection for this camera.
	  * Please read the description for the class for important
	  * information regarding this function.
	  * @return Perspective projection.
	  */
	Angel::mat4 getPerspectiveMatrix() const;
	/** Returns the orthographic projection for this camera.
	  * Please read the description for the class for important
	  * information regarding this function.
	  * @return Orthographic projection.
	  */
	Angel::mat4 getOrthographicMatrix() const
	{return Angel::Ortho(-.5*_aspect,.5*_aspect,-.5,.5,-1,_farClip);}
};

#endif //_CAMERAENTITY