#include "context.h"

ContextUptr Context::Create() {
  auto ctx = ContextUptr(new Context());
  if(!ctx) {
    std::cerr << "failed to create context" << std::endl;
    return nullptr;
  }
  if(!ctx->init()) {
    std::cerr << "failed to init context" << std::endl;
    return nullptr;
  }

  return std::move(ctx);
}

bool Context::init() {

  return true;
}