#version 130

//material properties
uniform sampler2D diffuseMap;
uniform vec4 diffuseColor;
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
uniform float lightBrightness[10];

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

	for(int i=0;i<10;i++){

		vec4 lightVec=lightPos[i]-fPosition;
		lightVec.w=0;
		vec4 lightVecNorm=normalize(lightVec);


		//Diffuse Pass
		float diffuseMult=clamp(dot(fNormal,lightVecNorm),0,1);
		diffusePass+=lightColor[i]*diffuseMult*(texture2D(diffuseMap,(fUV+uvOffset)*uvScale)+diffuseColor)*(1/pow(dot(lightVec,lightVec),lightFalloff[i]/2))*lightBrightness[i];

		

		//Specular Pass
		float specularMult;
		if(shininess<=0){
			specularMult=0;
		}else{
			specularMult=pow(dot(fNormal,normalize(viewVec+lightVecNorm)), shininess);
		}
		specularPass+=lightColor[i]*vec4(1,1,1,1)*specularMult*diffuseMult*lightBrightness[i];
		specularPass.w=1;

	}

	fColor=diffusePass+specularPass;

}
