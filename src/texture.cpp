#include "texture.h"

#include <stb_image.h>


inline uint32_t glTextureLayout(uint32_t format) {
  switch (format) {
    // RGB
    case GL_RGB:
    case GL_RGB8:
    case GL_RGB16:
    case GL_RGB8I:
    case GL_RGB16I:
    case GL_RGB32I:
    case GL_RGB8UI:
    case GL_RGB16UI:
    case GL_RGB32UI:
      return GL_RGB;

    // RGBA
    case GL_RGBA:
    case GL_RGBA8:
    case GL_RGBA16:
    case GL_RGBA8I:
    case GL_RGBA16I:
    case GL_RGBA32I:
    case GL_RGBA8UI:
    case GL_RGBA16UI:
    case GL_RGBA32UI:
      return GL_RGBA;

    // BGR
    case GL_BGR:
    case GL_BGR_INTEGER:
      return GL_BGR;

    // BGRA
    case GL_BGRA:
    case GL_BGRA_INTEGER:
      return GL_BGRA;
  }
  return 0;
}

inline uint32_t glTextureLayoutChannels(uint32_t format) {
  const uint8_t layout = glTextureLayout(format);
  switch (layout) {
    case GL_RGB:
    case GL_BGR:
      return 3;
    case GL_RGBA:
    case GL_BGRA:
      return 4;
  }
  return 0;
}

TextureUptr Texture::Create(int width, int height, uint32_t format,
                            uint32_t type, const void *pixels) {
  auto texture = TextureUptr(new Texture());
  texture->createTexture();
  texture->setTextureFormat(width, height, format, type, pixels);

  return std::move(texture);
}

TextureUptr Texture::CreateEmpty(int width, int height, uint32_t format,
                                 uint32_t type) {
  auto texture = TextureUptr(new Texture());
  texture->createTexture();

  // empty(white) texture
  std::vector<uint8_t> emptyData(width * height * glTextureLayoutChannels(format), 255);
  texture->setTextureFormat(width, height, format, type, &emptyData[0]);

  return std::move(texture);
}

Texture::~Texture() {
  if (mTextureID) {
    glDeleteTextures(1, &mTextureID);
  }
}

void Texture::SetFilter(uint32_t minFilter, uint32_t magFilter) const {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
}

void Texture::SetWrap(uint32_t sWrap, uint32_t tWrap) const {
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, sWrap);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, tWrap);
}

void Texture::SetBorderColor(const glm::vec4 &color) const {
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR,
                   glm::value_ptr(color));
}

void Texture::createTexture() {
  glGenTextures(1, &mTextureID);
  Bind();  // bind and set default filter and wrap option

  SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
  // SetFilter(GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
  SetFilter(GL_LINEAR, GL_LINEAR);
}

void Texture::setTextureFormat(int width, int height, uint32_t format,
                               uint32_t type, const void *pixels) {
  mWidth = width;
  mHeight = height;
  mFormat = format;
  mType = type;

  GLenum imageFormat = GL_RGBA;
  if (mFormat == GL_DEPTH_COMPONENT) {
    imageFormat = GL_DEPTH_COMPONENT;
  } else if (mFormat == GL_RGB || mFormat == GL_RGB16F ||
             mFormat == GL_RGB32F) {
    imageFormat = GL_RGB;
  } else if (mFormat == GL_RG || mFormat == GL_RG8 || mFormat == GL_RG16F ||
             mFormat == GL_RG32F) {
    imageFormat = GL_RG;
  } else if (mFormat == GL_RED || mFormat == GL_R16F || mFormat == GL_R32F) {
    imageFormat = GL_RED;
  }

  glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, imageFormat,
               mType, pixels);
  glGenerateMipmap(GL_TEXTURE_2D);
}