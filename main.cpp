#include <GL/glew.h>  // <- muse be included first
#include <GLFW/glfw3.h>

#include <iostream>

static void errorCallback(int errorCode, const char* errorDescription) {
  std::cerr << "Error : " << errorDescription << std::endl;
}

void keyCallback(GLFWwindow* wnd, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(wnd, GLFW_TRUE);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
  glfwSetErrorCallback(errorCallback);

  if (!glfwInit()) {
    std::cerr << "Error: failed to initialize GLFW" << std::endl;
    exit(EXIT_FAILURE);
  }

  const int wndWidth = 800;
  const int wndHeight = 600;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE,
                 GLFW_OPENGL_CORE_PROFILE);  // core profile (not compatible)
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
  glfwWindowHint(GLFW_SAMPLES, 4);

  GLFWwindow* wnd =
      glfwCreateWindow(wndWidth, wndHeight, "LineRender_Sample", NULL, NULL);

  if (!wnd) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  glfwMakeContextCurrent(
      wnd);  // GLFW가 현재 window을 main context로 만들도록 함

  glfwSetFramebufferSizeCallback(wnd,
                                 [](GLFWwindow* window, int width, int height) {
                                   glViewport(0, 0, width, height);
                                 });
  glfwSetKeyCallback(wnd, keyCallback);

  glewExperimental = GL_TRUE;  // configure to get all OpenGL extensions

  GLenum errorCode = glewInit();
  if (GLEW_OK != errorCode) {
    std::cerr << "Error : failed to initialize GLEW" << std::endl;

    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  if (!GLEW_VERSION_3_3) {
    std::cerr << "OpenGL 3.3 API is not available." << std::endl;

    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  std::cout << "OpenGL version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;
  std::cout << "Vendor : " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer : " << glGetString(GL_RENDER) << std::endl;

  while (!glfwWindowShouldClose(wnd)) {
    glfwSwapBuffers(wnd);
    glfwPollEvents();
  }

  glfwTerminate();

  exit(EXIT_SUCCESS);
}

