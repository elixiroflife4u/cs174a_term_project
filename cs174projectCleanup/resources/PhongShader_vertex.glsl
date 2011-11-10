#version 130

in vec4 vPosition;
in vec4 vNormal;
in vec2 vUV;

out vec4 fPosition;
out vec4 fNormal;
out vec2 fUV;

void main(){
	vec4 v=vPosition*.4;
	v.w=1;
	gl_Position=v;
	//gl_Position=vec4(.5,.5,.5,.1);
	fPosition=v;
	fNormal=vNormal;
	fUV=vUV;

}

