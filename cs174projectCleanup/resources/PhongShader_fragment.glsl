#version 130

uniform sampler2D diffuseMap;
uniform float shininess;

in vec4 fNormal;
in vec4 fPosition;
in vec2 fUV;

uniform vec2 uvScale;
uniform vec2 uvOffset;

out vec4 fColor;
void main(){
	fColor=vec4(1,1,1,1)*-fPosition.z;
}
