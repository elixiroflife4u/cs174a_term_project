#version 130

//material properties
uniform sampler2D diffuseMap;
uniform float shininess;

//pixel properties
in vec4 fNormal;
in vec4 fPosition;
in vec2 fUV;

uniform vec2 uvScale;
uniform vec2 uvOffset;

//lighting
uniform vec4 ambientColor;
uniform vec4 lightPos[10];
uniform float lightFalloff[10];
uniform vec4 lightColor[10];

//Camera Properties
uniform mat4 camTransform;
uniform vec4 camPos;

//pixel color output
out vec4 fColor;

void main(){
	vec4 diffusePass=vec4(0,0,0,1);
	vec4 specularPass=vec4(0,0,0,1);

	vec4 viewVec=camPos-fPosition;
	viewVec.w=0;
	viewVec=normalize(viewVec);

	for(int i=0;i<1;i++){

		vec4 lightVec=lightPos[i]-fPosition;
		lightVec.w=0;
		lightVec=normalize(lightVec);

		//Diffuse Pass
		float diffuseMult=clamp(dot(fNormal,lightVec),0,1);
		diffusePass+=lightColor[i]*diffuseMult;//*texture2D(diffuseMap,(fUV+uvOffset)*uvScale);

		//Specular Pass
		float specularMult=pow(dot(fNormal,normalize(viewVec+lightVec)), 50);
		specularPass+=vec4(1,1,1,1)*specularMult*diffuseMult;
		specularPass.w=1;

	}

	fColor=diffusePass+specularPass;

	//fColor=specularPass;
	

	//fColor=viewVec;

	//fColor=vec4(1,1,1,1)*dot;

	//fColor=vec4(1,1,1,1)*-fPosition.z+.1;

	//fColor=vec4(lightColor[4].x,lightColor[4].y,0,1);
	//fColor=vTransform*vec4(1,1,1,0);
}
