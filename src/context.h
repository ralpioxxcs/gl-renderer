#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include "common.h"

CLASS_PTR(Context)
class Context {
 public:
  static ContextUptr Create();

  void Render();

 private:
  Context() = default;
  bool init();
};

#endif