#ifndef GUARD_CTexture_h
#define GUARD_CTexture_h
#undef _UNICODE
#include "GlobalIncludes.h"
class CTextureManager;

/** @brief Class that wraps information about a texture. This class 
* won't be used directly by the users.
*/
class CTexture
{
  friend class CTextureManager; ///< manager is friend so that it can create the instance for this class (constructors are private)

public:
  /** @brief Specifies a color key to be used for the texture. The color
  * specified as arguments will be transparent when the texture
  * is rendered on the screen.
  */
  void SetColorKey(unsigned char Red, unsigned char Green, unsigned char Blue);

  /** @brief Returns the width of the texture
  */
  unsigned int GetWidth()  const  { return m_TextData.nWidth;  }
  /** @brief Returns the height of the texture.
  */
  unsigned int GetHeight() const  { return m_TextData.nHeight; }

  /** @brief Adds/release a reference for the texture. When ReleaseReference
  * is called and decreases the reference count to 0, the texture
  * is released from the texture manager.
  */
  void AddReference();
  void ReleaseReference();

  /** @brief Bind this texture with openGL: this texture becomes
  * the 'active' texture in openGL.
  */
  void Bind() const;

  inline GLuint getGlID(){return m_glId;}

protected:
  /** @brief Constructor which takes the filename as argument.
  * It loads the file and throw an exception if the load
  * failed.
  */
  CTexture(const std::string& strFileName);
  ~CTexture();

private:
  /** @brief Loads the texture from the specified file. Throws an
  * exception if the load failed.
  */
  void LoadFile(const std::string& strFileName);

  /** @brief Structure that contains the information about the texture.
  */
  struct STextureData
  {
    unsigned int   nWidth; ///< Width of the texture
    unsigned int   nHeight; ///< Height of the texture
    unsigned char* pData; ///< Byte array containing the texture data
  };
  STextureData m_TextData;

  mutable GLuint m_glId; ///< The openGL id associated with this texture.

  /** @brief Reference count of the number of images that still hold a reference
  * to this texture. When no images reference the texture anymore, it is
  * released.
  */
  int m_iRefCount;
  std::string m_strTextName; ///< The filename from which the texture was loaded from.
};
#endif