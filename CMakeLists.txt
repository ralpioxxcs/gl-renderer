cmake_minimum_required(VERSION 3.9)

project(opengl-cpp-project C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(opengl-cpp-project-sample main.cpp)

find_package(PkgConfig REQUIRED)
find_package(OpenCV REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_link_libraries(opengl-cpp-project-sample
  OpenGL::GL 
  OpenGL::GLU 
  GLEW::glew
  ${GLFW_LIBRARIES})

set_target_properties(opengl-cpp-project-sample PROPERTIES SUFFIX ".bin")
