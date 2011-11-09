#ifndef GUARD_RenderObject_h
#define GUARD_RenderObject_h
#include "GlobalIncludes.h"

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
	CRenderObject(const std::string&, point4*, int, vec3*, int, vec2*, int);
	//~CRenderObject();	 //no dyanamically allocated data 

private:
	// Loads the geometry(and material properties?) from the specified file. Throws an
	// exception if the load failed.
	void LoadFile(const std::string&);
	void sendDataToGPU(point4*, vec3*, vec2*);

	// The filename from which the texture was loaded from.
	size_t pointsMemorySize;
	size_t normalMemorySize;
	size_t texCoordsMemorySize;
	int numPointsToDraw;
	GLuint vao;
	GLuint buffer;

	std::string m_strTextName;
};

#endif
