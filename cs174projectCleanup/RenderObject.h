#ifndef GUARD_RenderObject_h
#define GUARD_RenderObject_h
#include "GlobalIncludes.h"
#include <vector>
#include <map>

typedef vec4 point4;
class CRenderObjectManager;

class CRenderObject
{
	friend class CRenderObjectManager;
public:
	std::string getName() const; //returns the name
	GLuint getVaoId() const;
	GLuint getBufferId() const;
	void activateObject(GLuint) const; //the one which activates the attributes
	void draw(GLuint = GL_TRIANGLES) const;
protected:
	CRenderObject(const std::string&);
	//CRenderObject(const std::string&, point4*, int, vec3*, int, vec2*, int);
	//~CRenderObject();	 //no dyanamically allocated data 

private:
	//functions
	
	// Loads the geometry(and material properties?) from the specified file. Throws an exception if the load failed.
	void LoadFile(const std::string&);
	
	//send the fata to gpu
	void sendDataToGPU();

	//function to calculate the tbn basis vectors
	void computeTangentBasis(std::vector<point4>& points, std::vector<vec3>& normals, std::vector<vec2>& textureCoord, 
		std::vector<vec3>& tangents, std::vector<vec3>& bitangents);
	
	//indexing and tangent adding related stuff
	void indexVBO_TBN(
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
		std::vector<vec3> & out_bitangents );
	//helper struct and function to find same vertex fast
	struct PackedVertex{
		vec4 position;
		vec2 uv;
		vec3 normal;
		bool operator<(const PackedVertex that) const{
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
		};
	};
	bool getSimilarVertexIndex_fast(PackedVertex & packed, 
									std::map<PackedVertex,unsigned short> & VertexToOutIndex, 
									unsigned short & result)
	{
		std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
		if ( it == VertexToOutIndex.end() ){
			return false;
		}else{
			result = it->second;
			return true;
		}
	}

	// member types
	//
	int numPointsToDraw;
	GLuint vao;
	GLuint buffer;
	GLuint vao_indices;
	GLuint buffer_indices;

	std::string m_strTextName;	// The filename from which the texture was loaded from.
	//
	size_t pointsMemorySize;
	size_t normalMemorySize; //used for normal, tangents, and bitangents.
	size_t texCoordsMemorySize;
	//
	std::vector<unsigned short> indices; //since an unsigned short is used for index size, the number of vertices must be less than approx 65k
	std::vector<point4> indexed_vertices;
	std::vector<vec3> indexed_normals;
	std::vector<vec3> indexed_tangents;
	std::vector<vec3> indexed_bitangents;
	std::vector<vec2> indexed_textureCoord;


};

#endif
