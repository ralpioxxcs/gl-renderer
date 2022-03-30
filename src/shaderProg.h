#ifndef __SHADERPROG_H__
#define __SHADERPROG_H__

#include "common.h"

CLASS_PTR(ShaderProg)
class ShaderProg {
 public:
  static ShaderProgUptr Create(const std::string& vertShaderFilename, const std::string& fragShaderFilename);
  ~ShaderProg();

  uint32_t Get() const { return mProgram; }
  void Activate() const;
  void Inactivate() const;
  void SetUniform(const std::string& name, bool value) const;
  void SetUniform(const std::string& name, int value) const;
  void SetUniform(const std::string& name, float value) const;
  void SetUniform(const std::string& name, const glm::vec2& value) const;
  void SetUniform(const std::string& name, const glm::vec3& value) const;
  void SetUniform(const std::string& name, const glm::vec4& value) const;
  void SetUniform(const std::string &name, const glm::mat4 &value) const;

  // vertex, fragment shader 파일 경로 반환
  static std::pair<std::string, std::string> GetShadersFilepath(std::string shaderFilename) {
    std::string vertShader = shaderFilename + ".vert";
    std::string fragShader = shaderFilename + ".frag";

    return std::make_pair(vertShader, fragShader);
  }

private:
  ShaderProg() {}
  bool init(const std::string& vertShaderFilename,
            const std::string& fragShaderFilename);
  bool loadFile(const std::string& filename, uint32_t &shader, GLenum shaderType);

  uint32_t mProgram;
  uint32_t mVertShader;
  uint32_t mFragShader;
};

#endif