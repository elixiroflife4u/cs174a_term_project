/*
singleton
name -> {creation of render object and telling it to store data on card.
		 draw call for said render object
		 removal of the said render object
		 }
*/
#ifndef GUARD_CRenderObjectManager_h
#define GUARD_CRenderObjectManager_h
#include "RenderObject.h"
#include <map>
class CRenderObjectManager
{
public:
	// Loads a given render object using file name
	CRenderObject* GetRenderObject(const std::string&);

	//CRenderObject* GetRenderObject(const std::string&, point4*, int, vec3*, int, vec2*, int);
  
	// Release the bindings for the object and remove from the map (unimplemented at the moment)
	bool ReleaseRenderObject(const std::string& strTextName);

	// Returns the single instance of the render object manager.
	// The manager is implemented as a singleton.
	static CRenderObjectManager* GetInstance();
	
protected:
	CRenderObjectManager();
	~CRenderObjectManager();

private:
	typedef std::map<std::string, CRenderObject*> TRenderObjectMap;
	TRenderObjectMap m_renderObjects;
};
#endif