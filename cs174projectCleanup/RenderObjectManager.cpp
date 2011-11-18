#include "RenderObjectManager.h"

using namespace std;

CRenderObjectManager::CRenderObjectManager(): m_renderObjects()
{}

CRenderObjectManager::~CRenderObjectManager()
{
	TRenderObjectMap::iterator iter = m_renderObjects.begin();
	for(; iter != m_renderObjects.end(); iter++)
	{
		if(iter->second)
			delete iter->second;
	}
}
CRenderObjectManager* CRenderObjectManager::GetInstance()
{
	static CRenderObjectManager Instance;
	return &Instance;
}
bool CRenderObjectManager::ReleaseRenderObject(const std::string& strObjName)
{
	bool found = false;
	TRenderObjectMap::iterator iter = m_renderObjects.find(strObjName);
	if(iter != m_renderObjects.end()){
		found = true;
		if(iter->second)
			delete iter->second;
		m_renderObjects.erase(iter);
	}
	return found;
}
// Loads a given render object using file name
CRenderObject* CRenderObjectManager::GetRenderObject(const std::string& strObjName)
{
	TRenderObjectMap::const_iterator iter = m_renderObjects.find(strObjName);
	if(iter != m_renderObjects.end()){
		return iter->second;
	}
	
	//not found. load the file
	CRenderObject* pNewRendObj = NULL;
	pNewRendObj = new CRenderObject(strObjName);
	m_renderObjects[strObjName] = pNewRendObj;
	return pNewRendObj;
}
/*
CRenderObject* CRenderObjectManager::GetRenderObject(const std::string& strObjName, point4* points, int pointsNum, 
													  vec3* normals, int normalNum, vec2* textcoord, int textcoordNum)
{
	//check if already loaded.
	TRenderObjectMap::const_iterator iter = m_renderObjects.find(strObjName);
	if(iter != m_renderObjects.end()){
		return iter->second;
	}
	
	//not found. load the file
	CRenderObject* pNewRendObj = NULL;
	pNewRendObj = new CRenderObject(strObjName,points, pointsNum,normals, normalNum,textcoord, textcoordNum);
	m_renderObjects[strObjName] = pNewRendObj;
	return pNewRendObj;
}
*/