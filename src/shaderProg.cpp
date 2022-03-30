#include "shaderProg.h"

std::optional<std::string> LoadTextFile(const std::string &filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    throw std::runtime_error("failed to open file : " + filename);
    // return {};
  }
  std::stringstream text;
  text << fin.rdbuf();
  return text.str();
}

ShaderProgUptr ShaderProg::Create(const std::string& vertShaderFilename, const std::string& fragShaderFilename) {
  auto shaderProg = ShaderProgUptr(new ShaderProg());
  if (!shaderProg) {
    std::cerr << "ShaderProg::failed to allocate shader program instance" << std::endl;
    return nullptr;
  }
  if (!shaderProg->init(vertShaderFilename, fragShaderFilename)) {
    std::cerr << "ShaderProg::failed to init shader program" << std::endl;
    return nullptr;
  }
  return std::move(shaderProg);
}

void ShaderProg::Activate() const { 
  glUseProgram(mProgram); 
}

void ShaderProg::Inactivate() const { 
  glUseProgram(0); 
}

void ShaderProg::SetUniform(const std::string& name, bool value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniform1i(loc, value);
}

void ShaderProg::SetUniform(const std::string& name, int value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniform1i(loc, value);
}

void ShaderProg::SetUniform(const std::string& name, float value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniform1f(loc, value);
}

void ShaderProg::SetUniform(const std::string& name,
                            const glm::vec2& value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniform2fv(loc, 1, glm::value_ptr(value));
}

void ShaderProg::SetUniform(const std::string& name,
                            const glm::vec3& value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniform3fv(loc, 1, glm::value_ptr(value));
}

void ShaderProg::SetUniform(const std::string& name,
                            const glm::vec4& value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniform4fv(loc, 1, glm::value_ptr(value));
}

void ShaderProg::SetUniform(const std::string& name,
                            const glm::mat4& value) const {
  auto loc = glGetUniformLocation(mProgram, name.c_str());
  glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
}

ShaderProg::~ShaderProg() {
  if (mVertShader) {
    glDeleteShader(mVertShader);
  }
  if (mFragShader) {
    glDeleteShader(mFragShader);
  }
  if (mProgram) {
    glDeleteProgram(mProgram);
  }
}

bool ShaderProg::init(const std::string& vertShaderFilename,
                      const std::string& fragShaderFilename) {
  if (!loadFile(vertShaderFilename, mVertShader, GL_VERTEX_SHADER)) {
    std::cerr << "ShaderProg::failed to load vertex shader file" << std::endl;
    return false;
  }
  if (!loadFile(fragShaderFilename, mFragShader, GL_FRAGMENT_SHADER)) {
    std::cerr << "ShaderProg::failed to load fragment shader file" << std::endl;
    return false;
  }

  // 셰이더 프로그램 생성 및 링킹
  mProgram = glCreateProgram();
  glAttachShader(mProgram, mVertShader);
  glAttachShader(mProgram, mFragShader);
  glLinkProgram(mProgram);

  // 성공 여부 체크
  if (!glIsProgram(mProgram)) {
    std::cerr << "ShaderProg::not a shader program" << std::endl;
    return false;
  }
  int success = 0;
  glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
  if (!success) {
    char message[1024];
    glGetProgramInfoLog(mProgram, 1024, nullptr, message);
    throw std::runtime_error("ShaderProg::failed to link shader program");
  }

  return true;
}

bool ShaderProg::loadFile(const std::string& filename, uint32_t& shader, GLenum shaderType) {
  auto result = LoadTextFile(filename);
  if (!result.has_value()) {
    return false;
  }

  // 파일로부터 텍스트 값 받아옴
  auto& code = result.value();
  const char* codePtr = code.c_str();
  int32_t codeLength = (int32_t)code.length();

  // 셰이더 컴파일
  shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, (const GLchar* const*)&codePtr, &codeLength);
  glCompileShader(shader);

  // 셰이더 컴파일 성공 여부 체크
  int success = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    char message[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, message);
    std::cerr << "ShaderProg::failed to compile shader : " << filename << std::endl;
    std::cerr << "ShaderProg::message :" << message << std::endl;
    return false;
  }
  return true;
}