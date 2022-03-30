#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "common.h"

typedef struct _bufferData {
  uint32_t type{0};   // GL_ARRAY_BUFFER, GL_INDEX_BUFFER ..
  uint32_t usage{0};  // GL_STATIC_DRAW, GL_DYNAMIC_DRAW ...
  size_t stride{0};   // vertex를 이루는 데이터 형식 (ex. x,y,z,r,g,b ...)
  size_t count{0};    // vertex의 총 갯수 
  const void* data{nullptr};
} BufferData;

CLASS_PTR(Buffer)
class Buffer {
 public:
  static BufferUptr Create(BufferData data);
  ~Buffer();

  uint32_t Get() const { return mBuffer; }
  size_t GetSize() const { return (mData.count * mData.stride); }
  size_t GetCount() const { return mData.count; }
  size_t GetStride() const { return mData.stride; }

  void Bind() const;
  void Unbind() const;
  void SetSubData(uint64_t offset, size_t size, const void *data);

private:
  Buffer(){};

  bool init(BufferData data);

  uint32_t mBuffer{0};
  BufferData mData;
};

#endif