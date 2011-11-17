#include "MobileEntity.h"
void MobileEntity::placeAtEdge(const GameEntity& g)
{

		///@todo implement
	// collision detection for walls - so that the player can "land" on them and run into them
	// perhaps abstract it to the Mobileentity level because other mobile entities will need hit detection for walls as well


	CollisionBox b1=getHitBox();
	CollisionBox b2=g.getHitBox();

	//Tells whether or not the midpoint is at all within the mid point of the other box
	vec3 d1=b1.getTranslate()-getVel()-b1.getDimensions()/3-b2.getPoint1();
	vec3 d2=b1.getTranslate()-getVel()+b1.getDimensions()/3-b2.getPoint2();
	vec3 midDist=b1.getTranslate()-b2.getTranslate();

	bool midInX=(d1.x>0)!=(d2.x>0);
	bool midInY=(d1.y>0)!=(d2.y>0);
	bool midInZ=(d1.z>0)!=(d2.z>0);

	if(!midInX&&!midInY&&getVel().z==0||
		!midInX&&!midInZ&&getVel().y==0||
		!midInZ&&!midInY&&getVel().x==0
		)
		return;
	


	vec3 newPos;

	//within the "x prism"
	float dir=0;
	float EASE_VAL=.05;
	float EASE_SCALE_VAL=3.0;
	if(midInY&&midInZ||!midInX){
		if(midDist.x!=0)dir=midDist.x/abs(midDist.x);
		else dir=0;

		if(abs(d1.x)>b1.getDimensions().x/EASE_SCALE_VAL||abs(d2.x)>b1.getDimensions().x/EASE_SCALE_VAL)dir=0;

		if(abs(d1.x)<abs(d2.x)){
			if(getVel().x<0)
			{
				newPos.x=b2.getPoint1().x+b1.getDimensions().x/2;
			}
		}else{
			if(getVel().x>0)
			{
				newPos.x=b2.getPoint2().x-b1.getDimensions().x/2;
			}
		}
		if(newPos.x!=0){
			setTranslateX(newPos.x);
			setVelX(0);
		}
		translate(EASE_VAL*dir,0,0);
	}
	//within the "y prism"
	if(midInX&&midInZ||!midInY){
		if(midDist.y!=0)dir=midDist.y/abs(midDist.y);
		else dir=0;

		if(abs(d1.y)>b1.getDimensions().y/EASE_SCALE_VAL||abs(d2.y)>b1.getDimensions().y/EASE_SCALE_VAL)dir=0;

		if(abs(d1.y)<abs(d2.y)){
			if(getVel().y<0)
			{
				newPos.y=b2.getPoint1().y+b1.getDimensions().y/2;
			}
		}else{
			if(getVel().y>0)
			{
				newPos.y=b2.getPoint2().y-b1.getDimensions().y/2;
			}
		}

		if(newPos.y!=0){
			setTranslateY(newPos.y);
			setVelY(0);
		}
		setVel(getVel()*.85);
		_jumpCount=1;
		if(dot(getVel(),getVel())<.01){
			setVel(0,0,0);
		}
		translate(0,EASE_VAL*dir,0);
	}
	
	//within the "z prism"
	if(midInX&&midInY||!midInZ){
		if(midDist.y!=0)dir=midDist.y/abs(midDist.y);
		else dir=0;

		if(abs(d1.z)>b1.getDimensions().z/EASE_SCALE_VAL||abs(d2.z)>b1.getDimensions().z/EASE_SCALE_VAL)dir=0;

		if(abs(d1.z)<abs(d2.z)){
			if(getVel().z<0)
			{
				newPos.z=b2.getPoint1().z+b1.getDimensions().z/2;
			}
		}else{
			if(getVel().z>0)
			{
				newPos.z=b2.getPoint2().z-b1.getDimensions().z/2;
			}
		}
		
		if(newPos.z!=0){
			setTranslateZ(newPos.z);
			setVelZ(0);
		}
		translate(0,0,EASE_VAL*dir);
	}

	vec3 v=getTranslate()-newPos;
}
void MobileEntity::jump(float force){
	if(_jumpCount>0){
		_jumpCount--;
		setVel(0,force,0);
	}
}