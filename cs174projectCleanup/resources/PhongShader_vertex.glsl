#version 130

//Input: vertex attributes these are in modelspace
in vec4 vPosition;
in vec4 vNormal;
in vec4 vTangent;
in vec4 vBitangent; //shouldn't these be vec3's?
in vec2 vUV;

//transformations that are constant for whole mesh
uniform mat4 vTransform;	//same as model transform
uniform mat4 camTransform; //same as view transform
uniform mat4 perspTransform; 

//Constants:
uniform vec2 uvScale;
uniform vec2 uvOffset; //what is this?

//Outputs: interpolated pixel properties
out vec4 fPosition_worldspace;
out vec4 fNormal_worldspace;
out vec2 fUV;

//normalized modelspace tbn basis
out vec4 o_vertexNormal_modelspace;
out vec4 o_vertexTangent_modelspace;
out vec4 o_vertexBitangent_modelspace;

void main(){
	// Position of the vertex, in worldspace
	fPosition_worldspace = vPosition*vTransform;

	// Output position of the vertex, in clip space
	gl_Position = fPosition_worldspace * camTransform * perspTransform;

	//normal in worldspace
	fNormal_worldspace   = vNormal;
	fNormal_worldspace.w = 0;
	fNormal_worldspace   = normalize(fNormal_worldspace * vTransform);

	fUV = (vUV + uvOffset) * uvScale; //texture coord

	//normalizing TBN basis
	o_vertexNormal_modelspace      = vNormal;
	o_vertexNormal_modelspace.w    = 0;
	o_vertexTangent_modelspace     = vTangent;
	o_vertexTangent_modelspace.w   = 0;
	o_vertexBitangent_modelspace   = vBitangent;
	o_vertexBitangent_modelspace.w = 0;

	o_vertexNormal_modelspace = normalize(o_vertexNormal_modelspace*vTransform);
	o_vertexTangent_modelspace = normalize(o_vertexTangent_modelspace*vTransform);
	o_vertexBitangent_modelspace = normalize(o_vertexBitangent_modelspace*vTransform);
	
}

