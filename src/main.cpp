#include "common.h"

#include "vertexLayout.h"
#include "buffer.h"
#include "shaderProg.h"
#include "texture.h"

static void OnErrorCallback(int errorCode, const char* errorDescription) {
  std::cerr << "glfw error callback : " << errorDescription << std::endl;
}

static void OnKeyCallback(GLFWwindow* wnd, int key, int scancode, int action,
                          int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
    glfwSetWindowShouldClose(wnd, GLFW_TRUE);
  }
}

static void OnFramebufferSizeCallback(GLFWwindow* window, int width,
                                      int height) {
  glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {
  GLFWwindow* window;

  if (!glfwInit()) {
    const char* desc = nullptr;
    glfwGetError(&desc);
    throw std::runtime_error("failed to initialize glfw (" + std::string(desc) + ")");
  }

#ifdef __APPLE__
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  const int wndWidth = 800;
  const int wndHeight = 600;
  const char* wndName = "window";

  window = glfwCreateWindow(wndWidth, wndHeight, wndName, nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    throw std::runtime_error("failed to intialize glfw window");
  }

  // GLFW가 현재 window을 main context로 만들도록 함
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("failed to loading opengl");
  }

  std::cout << "* OpenGL version : " << glGetString(GL_VERSION) << std::endl;
  std::cout << "* GLSL version : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
  std::cout << "* Vendor : " << glGetString(GL_VENDOR) << std::endl;

  OnFramebufferSizeCallback(window, wndWidth, wndHeight);
  glfwSetFramebufferSizeCallback(window, OnFramebufferSizeCallback);
  glfwSetKeyCallback(window, OnKeyCallback);
  glfwSetErrorCallback(OnErrorCallback);

  // std::string vertShdr = "box.vert";
  // std::string fragShdr = "box.frag";
  // auto shader = ShaderProg::Create(vertShdr, fragShdr);
  auto shaderFiles = ShaderProg::GetShadersFilepath("box");
  auto shader = ShaderProg::Create(shaderFiles.first, shaderFiles.second);
  if(!shader) {
    throw std::runtime_error("failed to init shader program");
  }

  auto vao = VertexLayout::Create();
  if(!vao) {
    throw std::runtime_error("failed to init VAO");
  }

  const int w = 100;
  const int h = 50;
  const std::vector<float> vertices = {
      // vertex coords (x,y,z)      // texture coords (x,y)
      (float)w, (float)h, 0.0f,     1.0f, 1.0f, // 1
      (float)w, 0.0f,     0.0f,     1.0f, 0.0f, // 2
      0.0f,     0.0f,     0.0f,     0.0f, 0.0f, // 3
      0.0f,     (float)h, 0.0f,     0.0f, 1.0f, // 4
  };

  const std::vector<uint32_t> indices = {
      0, 1, 3, // first
      1, 2, 3, // second
  };

  auto vbo = Buffer::Create(BufferData{
      GL_ARRAY_BUFFER,
      GL_STATIC_DRAW,
      sizeof(float),
      vertices.size(),
      vertices.data(),
  });
  if (!vbo) {
    throw std::runtime_error("failed to init VBO");
  }

  auto ibo = Buffer::Create(BufferData{
      GL_ELEMENT_ARRAY_BUFFER,
      GL_STATIC_DRAW,
      sizeof(uint32_t),
      indices.size(),
      indices.data(),
  });
  vao->SetAttribute(0, 3, GL_FLOAT, false, 5 * sizeof(float), 0);
  vao->SetAttribute(1, 2, GL_FLOAT, false, 5 * sizeof(float), sizeof(float) * 3);

  auto tex = Texture::CreateEmpty(w, h);
  if (!tex) {
    throw std::runtime_error("failed to init texture");
  }

  glActiveTexture(GL_TEXTURE0);
  tex->Bind();

  shader->Activate();
  shader->SetUniform("tex", 0);
  shader->SetUniform("resolution", glm::vec2(w, h));

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(float(wndWidth/2), float(wndHeight/2), 0.0f));
    glm::mat4 projection = glm::ortho(0.0f, float(wndWidth), 0.0f, float(wndHeight), -1.0f, 1.0f);
    glm::mat4 transform = projection * model;

    tex->Bind();

    shader->Activate();
    shader->SetUniform("transform", transform);
    shader->SetUniform("resolution", glm::vec2(w,h));
    shader->SetUniform("colorStart", glm::vec3(1.0f, 0.0f, 0.0f));
    shader->SetUniform("colorEnd", glm::vec3(1.0f , 0.5f, 0.0f));
    shader->SetUniform("gradWeight", 1.0f);
    shader->SetUniform("radius", 0.3f);

    vao->Bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    vao->Unbind();
    tex->Unbind();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
