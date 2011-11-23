#ifndef GUARD_RenderObject_h
#define GUARD_RenderObject_h
#include "GlobalIncludes.h"
#include <vector>
#include <map>

typedef vec4 point4;
class CRenderObjectManager;
/** @brief Class that handles storing the data for each vertices (points, normals, texture coord, tangents, bitangents)
* on the card. Once stored, the data is removed and the VAO and VBO id's are used to activate
* and draw stuff. Also uses indexed access which eleminates the need for duplicating the vertices.
*/
class CRenderObject
{
	friend class CRenderObjectManager; ///< manager is friend to provide access to private constructor (so that manager is the only one that can create instance of this class)
public:
	/** @brief return the file name */
	std::string getName() const;
	/** @brief returns the associated VAO id */
	GLuint getVaoId() const;
	/** @brief returns the associated VBO id */
	GLuint getBufferId() const;
	/** @brief activates the VAO and VBO the current */
	void activateObject(GLuint) const;
	/** @brief draw the required stuff */
	void draw(GLuint = GL_TRIANGLES) const;
protected:
	CRenderObject(const std::string&);
	//CRenderObject(const std::string&, point4*, int, vec3*, int, vec2*, int);
	//~CRenderObject();	 //no dyanamically allocated data 

private:
	//functions
	
	/** @brief Loads the geometry from the specified file. Throws an exception if the load failed.
	* uses the maya obj helper class for loading the obj and mtl files.
	*/
	void LoadFile(const std::string&);
	
	/** @brief send the fata to gpu */
	void sendDataToGPU();

	/** @brief  Calculates the tangents and bitangents. These two, along with normals, form the basis
	* vectors of TBN space.
	*/
	void computeTangentBasis(std::vector<point4>& points, std::vector<vec3>& normals, std::vector<vec2>& textureCoord, 
		std::vector<vec3>& tangents, std::vector<vec3>& bitangents);
	
	/** @brief Reads in the vertices information and adds up the tangents and bitangents for shared vertices.
	* It then makes an indices array and arrays storing only unique vertices. This saves up on space on the GPU
	*/
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
	/** @brief helper struct and function to find same vertex fast
	*/
	struct PackedVertex{
		vec4 position;
		vec2 uv;
		vec3 normal;
		bool operator<(const PackedVertex that) const{
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
		};
	};
	/** @brief function to find if the present packed vertices is unique or not.
	*/
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
	int numPointsToDraw; ///< number of points in the model
	GLuint vao;    ///< vao id of the model
	GLuint buffer; ///< vbo id of the model
	GLuint vao_indices; ///< vao id associated with the stride or indices array
	GLuint buffer_indices; ///< vbo id associated with stried or indices array

	std::string m_strTextName;	///< The filename from which the texture was loaded from.
	//
	size_t pointsMemorySize; ///< size of points memory
	size_t normalMemorySize; ///< size used for normal, tangents, and bitangents.
	size_t texCoordsMemorySize; ///< size of coord memory
	//
	std::vector<unsigned short> indices; ///< since an unsigned short is used for index size, the number of UNIQUE vertices must be less than approx 65k
	std::vector<point4> indexed_vertices; ///< vectors used for temporary storage of data
	std::vector<vec3> indexed_normals;
	std::vector<vec3> indexed_tangents;
	std::vector<vec3> indexed_bitangents;
	std::vector<vec2> indexed_textureCoord;


};

#endif
