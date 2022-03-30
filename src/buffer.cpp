#include "buffer.h"

BufferUptr Buffer::Create(const BufferData data) {
  auto buf = BufferUptr(new Buffer());
  if (!buf) {
    throw std::runtime_error("Buffer::failed to allocate buffer instance");
    return nullptr;
  }
  if (!buf->init(data)) {
    throw std::runtime_error("Buffer::failed to init buffer");
    return nullptr;
  }

  return std::move(buf);
}

Buffer::~Buffer() {
  if (mBuffer) {
    glDeleteBuffers(1, &mBuffer);
  }
}

void Buffer::Bind() const { 
  glBindBuffer(mData.type, mBuffer); 
}

void Buffer::Unbind() const { 
  glBindBuffer(mData.type, 0); 
}

void Buffer::SetSubData(uint64_t offset, size_t size, const void *data) {
  Bind();
  glBufferSubData(mData.type, offset, size, data);
}

bool Buffer::init(const BufferData data) {
  if(mBuffer != 0) {
    throw std::runtime_error("BufBuffer value is shouldn't be initialized");
    return false;
  }
  if ((data.stride * data.count) < 0) {
    throw std::runtime_error("Buffer::stride x count value should be greater than 0");
    return false;
  }
  mData = data;

  glGenBuffers(1, &mBuffer);

  Bind();

  glBufferData(mData.type, mData.stride * mData.count, mData.data, mData.usage);

  return true;
}