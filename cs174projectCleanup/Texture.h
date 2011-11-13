#ifndef GUARD_CTexture_h
#define GUARD_CTexture_h
#undef _UNICODE
#include "GlobalIncludes.h"
class CTextureManager;

// Class that wraps information about a texture. This class 
// won't be used directly by the users.
class CTexture
{
  friend class CTextureManager;

public:
  // Specifies a color key to be used for the texture. The color
  // specified as arguments will be transparent when the texture
  // is rendered on the screen.
  void SetColorKey(unsigned char Red, unsigned char Green, unsigned char Blue);

  // Returns the width of the texture
  unsigned int GetWidth()  const  { return m_TextData.nWidth;  }
  // Returns the height of the texture.
  unsigned int GetHeight() const  { return m_TextData.nHeight; }

  // Adds/release a reference for the texture. When ReleaseReference
  // is called and decreases the reference count to 0, the texture
  // is released from the texture manager.
  void AddReference();
  void ReleaseReference();

  // Bind this texture with openGL: this texture becomes
  // the 'active' texture in openGL.
  void Bind() const;

  inline GLuint getGlID(){return m_glId;}

protected:
  // Constructor which takes the filename as argument.
  // It loads the file and throw an exception if the load
  // failed.
  CTexture(const std::string& strFileName);
  ~CTexture();

private:
  // Loads the texture from the specified file. Throws an
  // exception if the load failed.
  void LoadFile(const std::string& strFileName);

  // Structure that contains the information about the texture.
  struct STextureData
  {
    // Width of the texture
    unsigned int   nWidth;
    // Height of the texture
    unsigned int   nHeight;
    // Byte array containing the texture data
    unsigned char* pData;
  };
  STextureData m_TextData;

  // The openGL id associated with this texture.
  mutable GLuint m_glId;

  // Reference count of the number of images that still hold a reference
  // to this texture. When no images reference the texture anymore, it is
  // released.
  int m_iRefCount;
  // The filename from which the texture was loaded from.
  std::string m_strTextName;
};
#endif