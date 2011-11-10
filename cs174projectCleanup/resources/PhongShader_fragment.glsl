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

//pixel color output
out vec4 fColor;

void main(){
	vec4 diffusePass=vec4(0,0,0,1);
	vec4 specularPass=vec4(0,0,0,1);

	for(int i=0;i<10;i++){
		//vec4 light

		diffusePass+=texture2D(diffuseMap,fUV)*lightColor[i];

		specularPass+=lightColor[i];
	}

	fColor=ambientColor+diffusePass+specularPass;

	fColor=vec4(1,1,1,1)*-fPosition.z+.1;
}
