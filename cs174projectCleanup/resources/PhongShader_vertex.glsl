#version 130

//vertex properties
in vec4 vPosition;
in vec4 vNormal;
in vec2 vUV;

//transformations
uniform mat4 vTransform;
uniform mat4 camTransform;
uniform mat4 perspTransform;

//interpolated pixel properties
out vec4 fPosition;
out vec4 fNormal;
out vec2 fUV;

void main(){
	fPosition=vPosition*vTransform;
	fNormal=vNormal;
	fNormal.w=0;
	fNormal=normalize(fNormal*vTransform);
	fUV=vUV;

	gl_Position=fPosition*camTransform*perspTransform;
}

