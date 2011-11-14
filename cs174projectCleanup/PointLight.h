#ifndef _POINTLIGHT
#define _POINTLIGHT

class PointLight: public WorldEntity{
private:
	vec3 _color;
	float _falloff;
	float _brightness;
public:
	PointLight(vec3 c=vec3(1,1,1), float f=0.0, float b=1.0)
		:_color(c),_falloff(f),_brightness(b)
	{}

	void incColor(vec3 c){_color+=c;}
	void setColor(vec3 c){_color=c;}
	void setColor(float r, float g, float b){setColor(vec3(r,g,b));}
	void setColorR(float r){_color.x=r;}
	void setColorG(float g){_color.y=g;}
	void setColorB(float b){_color.z=b;}

	void setFalloff(float f){_falloff=f;}
	void setBrightness(float b){_brightness=b;}

	vec3 getColor()const{return _color;}
	float getFalloff() const{return _falloff;}
	float getBrightness() const{return _brightness;}
};

#endif //_POINTLIGHT