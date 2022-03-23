#include "common.h"

#include <iostream>

static void OnErrorCallback(int errorCode, const char* errorDescription) {
  std::cerr << "Error : " << errorDescription << std::endl;
}

static void OnKeyCallback(GLFWwindow* wnd, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(wnd, GLFW_TRUE);
  }
}

static void OnFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
  if (!glfwInit()) {
    const char* desc = nullptr;
    glfwGetError(&desc);
    std::cerr << "Error: failed to initialize GLFW (" << desc << ")"
              << std::endl;
    return -1;
  }

  const int wndWidth = 800;
  const int wndHeight = 600;
  const char* wndName = "window";

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* wnd = glfwCreateWindow(wndWidth, wndHeight, wndName, nullptr, nullptr);
  if (!wnd) {
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(wnd);  // GLFW가 현재 window을 main context로 만들도록 함

  OnFramebufferSizeCallback(wnd, wndWidth, wndHeight);
  glfwSetFramebufferSizeCallback(wnd, OnFramebufferSizeCallback);
  glfwSetKeyCallback(wnd, OnKeyCallback);
  glfwSetErrorCallback(OnErrorCallback);

  std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer : " << glGetString(GL_RENDER) << std::endl;

  while (!glfwWindowShouldClose(wnd)) {
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(wnd);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
