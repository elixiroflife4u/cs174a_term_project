#ifndef GUARD_CRenderObjectManager_h
#define GUARD_CRenderObjectManager_h
#include "RenderObject.h"
#include <map>
/** @brief
* singleton
* name -> {creation of render object and telling it to store data on card. 
*		 draw call for said render object
*		 removal of the said render object
*		 }
*		 The objects themselves are RenderObject type. this class is just provides management interface
*/
class CRenderObjectManager
{
public:
	/** @brief Loads a given render object using file name */
	CRenderObject* GetRenderObject(const std::string&);

	//CRenderObject* GetRenderObject(const std::string&, point4*, int, vec3*, int, vec2*, int);
  
	/** @brief Release the bindings for the object and remove from the map */
	bool ReleaseRenderObject(const std::string& strTextName);

	/** @brief Returns the single instance of the render object manager.
	* The manager is implemented as a singleton.
	*/
	static CRenderObjectManager* GetInstance();
	
protected:
	/** @brief singleton to prevent accidental creation of another instance */
	CRenderObjectManager();
	~CRenderObjectManager();

private:
	typedef std::map<std::string, CRenderObject*> TRenderObjectMap; ///< map of file names with their objects
	TRenderObjectMap m_renderObjects; ///< RenderObjectMap type 
};
#endif