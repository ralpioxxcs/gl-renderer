#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "common.h"

CLASS_PTR(Texture)
class Texture {
 public:
  static TextureUptr Create(int width, int height, uint32_t format = GL_RGBA,
                            uint32_t type = GL_UNSIGNED_BYTE,
                            const void *pixels = nullptr);

  static TextureUptr CreateEmpty(int width, int height,
                                 uint32_t format = GL_RGBA,
                                 uint32_t type = GL_UNSIGNED_BYTE);

  ~Texture();

  inline uint32_t Get() const { return mTextureID; }
  inline int GetWidth() const { return mWidth; }
  inline int GetHeight() const { return mHeight; }
  inline uint32_t GetFormat() const { return mFormat; }
  inline uint32_t GetType() const { return mType; }
  inline void Bind() const { glBindTexture(GL_TEXTURE_2D, mTextureID); }
  inline void Unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

  void SetFilter(uint32_t minFilter, uint32_t magFilter) const;
  void SetWrap(uint32_t sWrap, uint32_t tWrap) const;
  void SetBorderColor(const glm::vec4 &color) const;

 private:
  Texture() {}
  explicit Texture(uint32_t format, uint32_t type)
      : mFormat(format), mType(type){};

  void createTexture();
  void setTextureFormat(int width, int height, uint32_t format, uint32_t type,
                        const void *pixels);

  uint32_t mTextureID{0};
  int mWidth{0};
  int mHeight{0};
  uint32_t mFormat{GL_RGBA};
  uint32_t mType{GL_UNSIGNED_BYTE};
};

#endif