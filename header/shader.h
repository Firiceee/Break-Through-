#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <string_view>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

enum class shaderType
{
    PROGRAM, VERTEX, FRAGMENT
};

std::string getStringFromFile(const std::string& filepath);
class Shader
{
public:
    Shader(const std::string& vertPath, const std::string& fragPath);
    void Use();
    void Delete();
    void Unbind();
    void SetInt(const std::string& name, GLint value);
    void SetUInt(const std::string& name, GLuint value);
    void SetFloat(const std::string& name, GLfloat value);
    void SetVec2(const std::string& name, const glm::vec2& vec);
    void SetVec3(const std::string& name, const glm::vec3& vec);
    void SetVec4(const std::string& name, const glm::vec4& vec);
    void SetMat3(const std::string& name, const glm::mat3& mat);
    void SetMat4(const std::string& name, const glm::mat4& mat);


private:
    GLuint m_ID;
    void ErrorHandling(GLuint shader, shaderType type);
};

std::ostream& operator<<(std::ostream& out, shaderType type);

#endif
