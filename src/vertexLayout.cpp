#include "vertexLayout.h"

VertexLayoutUptr VertexLayout::Create() {
  auto vl = VertexLayoutUptr(new VertexLayout());
  if (!vl) {
    std::cerr << "VertexLayout::failed to allocate vertexLayout instance" << std::endl;
    return nullptr;
  }
  if (!vl->init()) {
    std::cerr << "VertexLayout::failed to init vertexLayout" << std::endl;
    return nullptr;
  }

  return std::move(vl);
}

VertexLayout::~VertexLayout() {
  if (mVAO) {
    glDeleteVertexArrays(1, &mVAO);
  }
}

void VertexLayout::Bind() const { glBindVertexArray(mVAO); }

void VertexLayout::Unbind() const { glBindVertexArray(0); }

void VertexLayout::SetAttribute(int attribIdx, int size, int type,
                                bool normalized, size_t stride,
                                uint64_t offset) {
  std::cout << "VertexLayout::set vertex attributes" << std::endl;

  glEnableVertexAttribArray(attribIdx);
  glVertexAttribPointer(attribIdx, size, type, normalized, stride,
                        (const void*)offset);
}

bool VertexLayout::init() {
  std::cout << "VertexLayout::init vertex array object" << std::endl;

  std::cout << "VertexLayout::generate VAO" << std::endl;
  glGenVertexArrays(1, &mVAO);

  std::cout << "VertexLayout::bind VAO" << std::endl;
  glBindVertexArray(mVAO);

  return true;
}
