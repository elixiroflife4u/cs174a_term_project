#version 130

//Constants: samplers
uniform sampler2D diffuseMap;
uniform sampler2D NormalMap;

//Normal Map "Depth" Scaling
uniform float normalMapDepth;

//Constants: material properties
uniform vec4 diffuseColor;
uniform float shininess;
uniform float alpha;

//Constants:
uniform vec2 uvScale;
uniform vec2 uvOffset; //what is this?

//Constants: lighting
uniform vec4 ambientColor;
uniform vec4 lightPos[10];
uniform float lightFalloff[10];
uniform vec4 lightColor[10];
uniform float lightBrightness[10];

//Constants: Camera and moodel Properties
uniform mat4 vTransform;
uniform mat4 camTransform;
uniform vec4 camPos; //camera position in worldspace

//Inputs
in vec4 fPosition_worldspace;
in vec4 fNormal_worldspace;
in vec2 fUV;
in vec4 o_vertexNormal_modelspace;
in vec4 o_vertexTangent_modelspace;
in vec4 o_vertexBitangent_modelspace;



//Output: pixel color output
out vec4 fColor;

void main(){

	mat4 TBN = transpose(mat4(o_vertexTangent_modelspace,
							  o_vertexBitangent_modelspace,
							  o_vertexNormal_modelspace,
							  vec4(0,0,0,0) )); //from worldspace to tbn space 4x4 since every normal is 4x4.

	vec4 diffusePass  = vec4(0,0,0,1);
	vec4 specularPass = vec4(0,0,0,0);

	vec4 viewVec = camPos-fPosition_worldspace;
	viewVec.w    = 0;
	vec4 viewVec_tbn      = normalize(TBN * (normalize(viewVec))); //eye direction in tbn space
	/////////
	//viewVec_tbn      =  (normalize(viewVec)); //in tbn space

	// some texture color
	vec4 texColor = texture2D(diffuseMap, fUV); //fUV has offset and stuff already applied.

	// Local normal, in tangent space. V tex coordinate is inverted because normal map is in TGA (not in DDS)
	//vec4 TextureNormal_tangentspace = vec4(normalize(texture2D( NormalMap, vec2(fUV.x,-fUV.y) ).rgb * 2.0 - 1.0), 0);
	vec4 TextureNormal_tangentspace = vec4(normalize(texture2D( NormalMap, vec2(fUV.x, fUV.y) ).rgb * 2.0 - 1.0), 0);

	vec4 n = normalize(normalMapDepth*TextureNormal_tangentspace+(1-normalMapDepth)*vec4(0,0,1,0));
	/////////
	//n = fNormal_worldspace;

	if(dot(viewVec,fNormal_worldspace)<0){
		return;
	}

	for(int i=0; i<10; i++)
	{
		vec4 lightVec = lightPos[i] - fPosition_worldspace;
		lightVec.w    = 0;
		vec4 lightVecNorm_tbn = normalize(TBN * normalize(lightVec)); //in tbn space

		////////
		//lightVecNorm_tbn = (normalize(lightVec)); //in tbn space

		//Diffuse Pass
		float diffuseMult = dot(n, lightVecNorm_tbn);
		diffusePass  += max(lightColor[i]* diffuseMult * (texColor + diffuseColor) * (1/pow(dot(lightVec, lightVec), lightFalloff[i]/2)) * lightBrightness[i],vec4(0,0,0,1));
		diffusePass   = clamp(diffusePass, 0.0, 1.0);


		//Specular Pass
		float specularMult;
		if(shininess <= 0){
			specularMult = 0;
		}else{
			specularMult = pow(max(dot(viewVec_tbn, normalize(-reflect(lightVecNorm_tbn, n))) ,0.0), shininess);
		}
		specularPass += lightColor[i] * specularMult * diffuseMult * lightBrightness[i];
		specularPass  = clamp(specularPass,0.0,1.0);
	}

	diffusePass.w = alpha;//*texColor.w;

	float fogIntensity=0;
	float fogMult=clamp(dot(viewVec,viewVec)*.0001,0.0,1.0)*fogIntensity;
	vec4 fogColor=vec4(.05,.075,.1,0);
	fogColor=vec4(1,1,1,0);

	fColor = vec4(ambientColor.xyz,0)+diffusePass+specularPass;//+fogPass;

	fColor=fColor*(1-fogMult)+fogColor*fogMult;

}
