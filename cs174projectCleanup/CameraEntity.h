#ifndef _CAMERAENTITY
#define _CAMERAENTITY

#include "WorldEntity.h"   //Scene

class CameraEntity:private WorldEntity{
private:
	
public:
	void setup();
	void update();
	void clean();
	
};

#endif //_CAMERAENTITY
