#include "RenderObject.h"
using namespace std;

CRenderObject::CRenderObject(const std::string& fileName)
{
	m_strTextName = fileName;
	LoadFile(fileName);
	//cout<<"done loading"<<endl;
}
/*
CRenderObject::CRenderObject(const std::string& fileName, point4 *points, 
							 int numVertices, vec3 *normals, int numNormals, 
							 vec2 *textureCoord,  int numTexElem)
							 :pointsMemorySize(numVertices*sizeof(point4)), normalMemorySize(numNormals*sizeof(vec3)), 
							  texCoordsMemorySize(numTexElem*sizeof(vec2)), numPointsToDraw(numVertices), vao(0), buffer(0)
{
	m_strTextName = fileName;
	sendDataToGPU(points, normals, textureCoord);
}
*/
void CRenderObject::LoadFile(const std::string& fileName)
{
	//get the file name
	char *cstr = new char[fileName.size()+1];
	strcpy(cstr, fileName.c_str());
	//load the file.
	objLoader *objData = new objLoader();
	objData->load(cstr);

	//std::cout<<"num of vertices: "<<objData->vertexCount<<"Normals: "<<objData->normalCount<<"texcoord: "<<objData->textureCount<<std::endl;
	//std::cout<<"num of faces: "<<objData->faceCount<<std::endl;
	// set the size in bytes information for each of the 3 types.
	
	numPointsToDraw     = (objData->faceCount)*3;

	///use vectors instead
	std::vector<point4> points;
	std::vector<vec2> textureCoord;
	std::vector<vec3> normals;
	std::vector<vec3> tangents;
	std::vector<vec3> bitangents;
	
	//allocate memory for them
	int position        = 0;
	for(int i = 0; i < objData->faceCount; i++){
		
		obj_face *o	  = objData->faceList[i];
		int numpoints = o->vertex_count;

		if(numpoints != 3){
			cout<<"found a face with number of vertices not equal to three. aborthing";
			exit(1);
		}
		//store values for each of the three types.
		for(int j=0; j < numpoints; j++){
			obj_vector *pointer;
			pointer					= objData->vertexList[o->vertex_index[j]];
			points.push_back( point4(pointer->e[0], pointer->e[1], pointer->e[2], 1.f));

			pointer					= objData->normalList[o->normal_index[j]];
			normals.push_back(vec3(pointer->e[0], pointer->e[1], pointer->e[2]));

			pointer					= objData->textureList[o->texture_index[j]];
			textureCoord.push_back(vec2(pointer->e[0], pointer->e[1]));
		}
	}
	//compute the basis vectors
	computeTangentBasis(points, normals, textureCoord, tangents, bitangents);
	//clear the output arrays
	indices.clear();
	indexed_vertices.clear();
	indexed_textureCoord.clear();
	indexed_normals.clear();
	indexed_tangents.clear();
	indexed_bitangents.clear();
	//index our arrary. Basically, we can to have just one copy of a type but provide a stride vector
	//to help gpu get the points. Also, for every vertex(same position, same normal, and same textureCoordinates)
	//we want to add or avg the tangents and bitangents.
	indexVBO_TBN(points, textureCoord, normals, tangents, bitangents, 
		indices, indexed_vertices, indexed_textureCoord, indexed_normals, indexed_tangents, indexed_bitangents);

	pointsMemorySize = indexed_vertices.size()*sizeof(point4);
	normalMemorySize = indexed_normals.size()*sizeof(vec3);
	texCoordsMemorySize = indexed_textureCoord.size()*sizeof(vec2);


	//send the data to gpu
	sendDataToGPU();
	//delete the data
	delete []cstr;
	//note do not clear the indices!
	indexed_vertices.clear();
	indexed_textureCoord.clear();
	indexed_normals.clear();
	indexed_tangents.clear();
	indexed_bitangents.clear();
}
void CRenderObject::sendDataToGPU()
{

	//get buffer id's and make them the active ones. only time vao and buffer variables modified.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	
	//allocate the buffer
	glBufferData(GL_ARRAY_BUFFER, (pointsMemorySize + normalMemorySize*3 + texCoordsMemorySize), NULL, GL_STATIC_DRAW);
	//store points
    glBufferSubData(GL_ARRAY_BUFFER, 0								       , pointsMemorySize, &indexed_vertices[0]);
	//store normals
    glBufferSubData(GL_ARRAY_BUFFER, pointsMemorySize	 			       , normalMemorySize, &indexed_normals[0]);
	//store tangets
	glBufferSubData(GL_ARRAY_BUFFER, pointsMemorySize + normalMemorySize   , normalMemorySize, &indexed_tangents[0]);
	//store bitangents
	glBufferSubData(GL_ARRAY_BUFFER, pointsMemorySize + 2*normalMemorySize , normalMemorySize, &indexed_bitangents[0]);
	//store texturecoord.
	glBufferSubData(GL_ARRAY_BUFFER, pointsMemorySize + 3*normalMemorySize , texCoordsMemorySize, &indexed_textureCoord[0]);

	//put indices in
	glGenBuffers(1, &buffer_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}
void CRenderObject::activateObject(GLuint linkedShaderProgram) const
{
	//make the vao and bo the current ones
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //TODO: is this the right command and do we even need it??

	//define the position of vertex in buffer and enable the attribute
	GLuint vPosition   = glGetAttribLocation(linkedShaderProgram, "vPosition");
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);

    //define the position of normals in buffer and enable the attribute
	GLuint vNormal     = glGetAttribLocation(linkedShaderProgram, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,     BUFFER_OFFSET(pointsMemorySize));

	//define the position of tangents in buffer and enable the attribute
	GLuint vTangents   = glGetAttribLocation(linkedShaderProgram, "vTangent");
    glEnableVertexAttribArray(vTangents);
    glVertexAttribPointer(vTangents, 3, GL_FLOAT, GL_FALSE, 0,   BUFFER_OFFSET(pointsMemorySize +  normalMemorySize));

	//define the position of bitangents in buffer and enable the attribute
	GLuint vBitangents = glGetAttribLocation(linkedShaderProgram, "vBitangent");
    glEnableVertexAttribArray(vBitangents);
    glVertexAttribPointer(vBitangents, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(pointsMemorySize + 2*normalMemorySize));

	//define the position of texturecoord  in buffer and enable the attribute
	GLuint vTexCoord   = glGetAttribLocation( linkedShaderProgram, "vUV" );
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,   BUFFER_OFFSET(pointsMemorySize + 3*normalMemorySize));

}
void CRenderObject::computeTangentBasis(std::vector<point4>& vertices, std::vector<vec3>& normals, std::vector<vec2>& textureCoord, 
		std::vector<vec3>& tangents, std::vector<vec3>& bitangents)
{
	for ( int i=0; i<vertices.size(); i+=3 ){

		// Shortcuts for vertices
		vec3 v0 = vertices[i+0].Vec4ToVec3();
		vec3 v1 = vertices[i+1].Vec4ToVec3();
		vec3 v2 = vertices[i+2].Vec4ToVec3();

		// Shortcuts for UVs
		vec2 & uv0 = textureCoord[i+0];
		vec2 & uv1 = textureCoord[i+1];
		vec2 & uv2 = textureCoord[i+2];

		// Edges of the triangle : postion delta
		vec3 deltaPos1 = v1-v0;
		vec3 deltaPos2 = v2-v0;

		// UV delta
		vec2 deltaUV1 = uv1-uv0;
		vec2 deltaUV2 = uv2-uv0;

		float r        = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		vec3 tangent   = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y) * r;
		vec3 bitangent = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x) * r;

		// Set the same tangent for all three vertices of the triangle.
		// They will be merged later
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);

		// Same thing for binormals
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);

	}

	//  make the tangent perpendicular to the normal so that inverse for tbn can be calcualted using a transpose
	// code and other related help from here: http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-13-normal-mapping/#top
	for ( int i=0; i<vertices.size(); i+=1 )
    {
        vec3 & n = normals[i];
        vec3 & t = tangents[i];
        vec3 & b = bitangents[i];
        
        // Gram-Schmidt orthogonalize
		t = normalize(t - n * dot(n, t));
        
        // Calculate handedness
		if (dot(cross(n, t), b) < 0.0f){
			t = t * -1.0f;
		}

    }
}
void CRenderObject::indexVBO_TBN(
		std::vector<point4> & in_vertices,
		std::vector<vec2> & in_uvs,
		std::vector<vec3> & in_normals,
		std::vector<vec3> & in_tangents,
		std::vector<vec3> & in_bitangents,

		std::vector<unsigned short> & out_indices,
		std::vector<point4> & out_vertices,
		std::vector<vec2> & out_uvs,
		std::vector<vec3> & out_normals,
		std::vector<vec3> & out_tangents,
		std::vector<vec3> & out_bitangents )
{
	std::map<PackedVertex,unsigned short> VertexToOutIndex;
	// For each input vertex
	for ( unsigned int i=0; i<in_vertices.size(); i++ ){

		// Try to find a similar vertex in the vertextooutindex map
		unsigned short index;
		PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};
		bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

		if ( found ){ 
			// A similar vertex is already in the VBO(that will be created), use it instead !
			out_indices.push_back( index );
			// Average or add (currently add) the tangents and the bitangents
			out_tangents[index] += in_tangents[i];
			out_bitangents[index] += in_bitangents[i];

		}else{
			// If vertex not present, it needs to be added in the output data (or the VBO).
			out_vertices  .push_back( in_vertices[i]);
			out_uvs       .push_back( in_uvs[i]);
			out_normals   .push_back( in_normals[i]);
			out_tangents  .push_back( in_tangents[i]);
			out_bitangents.push_back( in_bitangents[i]);
			//updated the index array and update the map
			///Problematic? No since we add the data to out_vertices before checking its size therefore size never going to be 0
			unsigned short newindex = (unsigned short)out_vertices.size() - 1;
			out_indices   .push_back( newindex );
			VertexToOutIndex[packed] = newindex;
		}
	}
}

GLuint CRenderObject::getVaoId() const
{
	return vao;
}
GLuint CRenderObject::getBufferId() const
{
	return buffer;
}
std::string CRenderObject::getName() const
{
	return m_strTextName;
}

void CRenderObject::draw(GLuint type) const
{
	//std::cout<<numPointsToDraw<<std::endl;
	glBindVertexArray(this->getVaoId());
	//glDrawArrays( type, 0, this->numPointsToDraw);
	glDrawElements(
			GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT, // type
			(void*)0           // element array buffer offset
			); //it works (surprisingly) even with subbuffer.
}