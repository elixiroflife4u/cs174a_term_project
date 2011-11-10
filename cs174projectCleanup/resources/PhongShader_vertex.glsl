#version 130

//vertex properties
in vec4 vPosition;
in vec4 vNormal;
in vec2 vUV;

//transformations
uniform mat4 vTransform;
uniform mat4 camTransform;

//interpolated pixel properties
out vec4 fPosition;
out vec4 fNormal;
out vec2 fUV;

void main(){
	//DELETE//
	vec4 v=vPosition*.4;
	v.w=1;
	gl_Position=v;
	//END DELETE//

	fPosition=vPosition*vTransform;
	//DELETE//
	fPosition=v;
	//END DELETE//
	fNormal=normalize(vNormal*vTransform);
	fUV=vUV;

	//gl_Position=fPosition*camTransform;
}

