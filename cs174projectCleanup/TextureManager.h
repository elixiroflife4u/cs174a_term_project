#ifndef GUARD_CTextureManager_h
#define GUARD_CTextureManager_h
#include "Texture.h"
#include <map>
/** @brief The texture manager provides an external interfact for managing textures. It takes 
* care of loading textures(when needed) and returning the Texture object type. 
* The texture manager avoid a same texture to be loaded multiple
* times. It keeps a map containing all the already loaded textures. This class does
* not bind the texture though and that has to be done by calling the function bind() in CTexture manually.
*/
class CTextureManager
{
public:
  /** @brief Loads a texture specified by its filename. If the texture is not
  * loaded already, the texture manager will load it, store it and
  * return it. Otherwise it simply returns the existing one.
  */
  CTexture* GetTexture(const std::string& strTextName);
  
  /** @brief Release the texture specified by its filename. Returns true if
  * the texture was found, otherwise false.
  */
  bool ReleaseTexture(const std::string& strTextName);

  /** @brief Returns the single instance of the texture manager.
  * The manager is implemented as a singleton.
  */
  static CTextureManager* GetInstance();

protected:
  /** @brief Both constructor and destructor are protected to make
  * it impossible to create an instance directly.
  */
  CTextureManager();
  ~CTextureManager();

private:
  typedef std::map<std::string, CTexture*> TTextureMap; ///< The map of already loaded textures. There are indexed
  TTextureMap m_Textures; ///< using their filename.
};
#endif