#version 130

//material properties
uniform sampler2D diffuseMap;
uniform vec4 diffuseColor;
uniform float shininess;
uniform float alpha;

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
	vec4 specularPass=vec4(0,0,0,0);

	vec4 viewVec=camPos-fPosition;
	viewVec.w=0;
	viewVec=normalize(viewVec);

	vec4 texColor=texture2D(diffuseMap,(fUV+uvOffset)*uvScale);

	for(int i=0;i<10;i++){
		vec4 lightVec=lightPos[i]-fPosition;
		lightVec.w=0;
		vec4 lightVecNorm=normalize(lightVec);

		//Diffuse Pass
		float diffuseMult=dot(fNormal,lightVecNorm);
		diffusePass+=lightColor[i]*diffuseMult*(texColor+diffuseColor)*(1/pow(dot(lightVec,lightVec),lightFalloff[i]/2))*lightBrightness[i];
		diffusePass=clamp(diffusePass,0.0,1.0);


		//Specular Pass
		float specularMult;
		if(shininess<=0){
			specularMult=0;
		}else{
			specularMult=pow(max(dot(viewVec,normalize(-reflect(lightVecNorm,fNormal))),0.0), shininess);
		}
		specularPass+=lightColor[i]*specularMult*diffuseMult*lightBrightness[i];
		specularPass=clamp(specularPass,0.0,1.0);
	}

	diffusePass.w=alpha;//*texColor.w;

	fColor=ambientColor+diffusePass+specularPass;
}
