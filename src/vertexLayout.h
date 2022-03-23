#ifndef __VERTEX_LAYOUT_H__
#define __VERTEX_LAYOUT_H__

#include "common.h"

CLASS_PTR(VertexLayout)
class VertexLayout {
 public:
  static VertexLayoutUptr Create();
  ~VertexLayout();

  uint32_t Get() const { return mVAO; }
  void Bind() const;
  void Unbind() const;
  void SetAttribute(int attribIdx, int size, int type, bool normalized, size_t stride, uint64_t offset);

 private:
  VertexLayout() {};

  bool init();
  uint32_t mVAO{0};
};

#endif // __VERTEX_LAYOUT_H__