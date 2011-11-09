#include "RenderObject.h"
using namespace std;

CRenderObject::CRenderObject(const std::string& fileName)
{
	m_strTextName = fileName;
	LoadFile(fileName);
	cout<<"done loading"<<endl;
}

CRenderObject::CRenderObject(const std::string& fileName, point4 *points, 
							 int numVertices, vec3 *normals, int numNormals, 
							 vec2 *textureCoord,  int numTexElem)
							 :pointsMemorySize(numVertices*sizeof(point4)), normalMemorySize(numNormals*sizeof(vec3)), 
							  texCoordsMemorySize(numTexElem*sizeof(vec2)), numPointsToDraw(numVertices), vao(0), buffer(0)
{
	m_strTextName = fileName;
	sendDataToGPU(points, normals, textureCoord);
}
void CRenderObject::LoadFile(const std::string& fileName)
{
	//get the file name
	char *cstr = new char[fileName.size()+1];
	strcpy(cstr, fileName.c_str());
	//load the file.
	objLoader *objData = new objLoader();
	objData->load(cstr);

	std::cout<<"num of vertices: "<<objData->vertexCount<<"Normals: "<<objData->normalCount<<"texcoord: "<<objData->textureCount<<std::endl;
	std::cout<<"num of faces: "<<objData->faceCount<<std::endl;
	// set the size in bytes information for each of the 3 types.
	numPointsToDraw     = (objData->faceCount)*3;
	pointsMemorySize    = numPointsToDraw*sizeof(point4);
	normalMemorySize    = numPointsToDraw*sizeof(vec3);
	texCoordsMemorySize = numPointsToDraw*sizeof(vec2);
	//allocate memory for them
	point4 *points      = new point4[numPointsToDraw];
	vec3 *normals       = new vec3[numPointsToDraw];
	vec2 *textureCoord  = new vec2[numPointsToDraw]; //assuming that texture coord is 2-d
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
			points[position]		= point4(pointer->e[0], pointer->e[1], pointer->e[2], 1.f);

			pointer					= objData->normalList[o->normal_index[j]];
			normals[position]		= vec3(pointer->e[0], pointer->e[1], pointer->e[2]);

			pointer					= objData->textureList[o->texture_index[j]];
			textureCoord[position]  = vec2(pointer->e[0], pointer->e[1]);
			position++;
		}
	}
	//send the data to gpu
	sendDataToGPU(points, normals, textureCoord);
	//delete the data
	delete []cstr;
	delete []points;
	delete []normals;
	delete []textureCoord;
}
void CRenderObject::sendDataToGPU(point4 *points, vec3 *normals, vec2 *textureCoord)
{

	for(int i=0;i<100;i++){
		//std::cout<<pointsMemorySize/sizeof(point4)<<std::endl;
	}

	//get buffer id's and make them the active ones. only time vao and buffer variables modified.
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
	//allocate the buffer
	glBufferData(GL_ARRAY_BUFFER, (pointsMemorySize + normalMemorySize + texCoordsMemorySize), NULL, GL_STATIC_DRAW);
	//store points
    glBufferSubData(GL_ARRAY_BUFFER, 0								     , pointsMemorySize, points);
	//store normals
    glBufferSubData(GL_ARRAY_BUFFER, pointsMemorySize	 			     , normalMemorySize, normals);
	//store texturecoord.
	glBufferSubData(GL_ARRAY_BUFFER, pointsMemorySize + normalMemorySize , texCoordsMemorySize, textureCoord);
}
void CRenderObject::activateObject(GLuint linkedShaderProgram) const
{
	//make the vao and bo the current ones
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, buffer); //TODO: is this the right command and do we even need it??

	//define the position of vertex in buffer and enable the attribute
	GLuint vPosition = glGetAttribLocation(linkedShaderProgram, "vPosition");
    glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(vPosition);

    //define the position of normals in buffer and enable the attribute
	GLuint vNormal = glGetAttribLocation(linkedShaderProgram, "vNormal");
    glEnableVertexAttribArray(vNormal);
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,   BUFFER_OFFSET(pointsMemorySize));

	//define the position of texturecoord  in buffer and enable the attribute
	GLuint vTexCoord = glGetAttribLocation( linkedShaderProgram, "vTexCoord" );
    glEnableVertexAttribArray( vTexCoord );
    glVertexAttribPointer(vTexCoord, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(pointsMemorySize + normalMemorySize));

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
	glDrawArrays( type, 0, this->numPointsToDraw);
}