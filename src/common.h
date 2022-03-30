#ifndef __GL_COMMON_H__
#define __GL_COMMON_H__

#include <fstream>
#include <optional>
#include <memory>
#include <filesystem>
#include <string>
#include <chrono>
#include <iostream>
#include <stdexcept>

// smart-pointer class definer
#define CLASS_PTR(className)                          \
  class className;                                    \
  using className##Uptr = std::unique_ptr<className>; \
  using className##Ptr = std::shared_ptr<className>;

// OpenGL
// WARNING : should be included before glfw
#define __gl3_h_
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#endif
