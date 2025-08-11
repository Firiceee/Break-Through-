#include "header/shader.h"

std::string getStringFromFile(const std::string& filepath)
{
    std::fstream file(filepath);
    if (!file.is_open())
    {
        std::cerr << "Could not open the file: " << filepath << std::endl;
        throw std::runtime_error("File not loaded");
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::ostream& operator<<(std::ostream& out, shaderType type)
{
    switch (type)
    {
    case shaderType::PROGRAM:
        return out << "PROGRAM";
    case shaderType::FRAGMENT:
        return out << "FRAGMENT";
    case shaderType::VERTEX:
        return out << "VERTEX";
    case shaderType::GEOMETRY:
        return out << "GEOMETRY";
    }

    return out;
}


void Shader::Delete()
{
    glDeleteProgram(m_ID);
}

Shader::~Shader()
{
    Delete();
}

void Shader::ErrorHandling(GLuint shader, shaderType type)
{
    int success;
    if (type != shaderType::PROGRAM)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[1024];
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Could not compile the shader" << type << " because " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[1024];
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "Could not link the shader " << type << " because " << infoLog << std::endl;
            std::cout << infoLog;
        }
    }
}

void Shader::Unbind()
{
    glUseProgram(0);
}
Shader& Shader::Use()
{
    glUseProgram(m_ID);
    return *this;
}
void Shader::SetFloat(const std::string& name, GLfloat value)
{
    glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
}

void Shader::SetInt(const std::string& name, GLint value)
{
    glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetUInt(const std::string& name, GLuint value)
{
    glUniform1ui(glGetUniformLocation(m_ID, name.c_str()), value);
}
void Shader::SetMat3(const std::string& name, const glm::mat3& mat)
{
    glUniformMatrix3fv(glGetUniformLocation(m_ID, name.c_str()),
        1, GL_FALSE, glm::value_ptr(mat));
}
void Shader::SetMat4(const std::string& name, const glm::mat4& mat)
{
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()),
        1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetVec2(const std::string& name, const glm::vec2& vec)
{
    glUniform2f(glGetUniformLocation(m_ID, name.c_str()), vec.x, vec.y);

}
void Shader::SetVec3(const std::string& name, const glm::vec3& vec)
{
    glUniform3f(glGetUniformLocation(m_ID, name.c_str()), vec.x, vec.y, vec.z);

}
void Shader::SetVec4(const std::string& name, const glm::vec4& vec)
{
    glUniform4f(glGetUniformLocation(m_ID, name.c_str()), vec.x, vec.y, vec.z, vec.w);

}


Shader::Shader(const std::string& vertPath, const std::string& fragPath, const std::string& geometryPath)
{
    std::string vert;
    std::string frag;
    std::string geometry;

    bool containGeometryShader = !geometryPath.empty();

    try
    {
        vert = getStringFromFile(vertPath);
        frag = getStringFromFile(fragPath);
        if (containGeometryShader)
        {
            geometry = getStringFromFile(geometryPath);
        }
    }
    catch (...)
    {
        std::cerr << "Could not reach file for Shader constructor" << std::endl;
    }

    const char* vertSourceCode = vert.c_str();
    const char* fragSourceCode = frag.c_str();

    GLuint  fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    GLuint  vertShader = glCreateShader((GL_VERTEX_SHADER));

    glShaderSource(fragShader, 1, &fragSourceCode, nullptr);
    glShaderSource(vertShader, 1, &vertSourceCode, nullptr);

    glCompileShader(fragShader);
    glCompileShader(vertShader);
    ErrorHandling(fragShader, shaderType::FRAGMENT);
    ErrorHandling(vertShader, shaderType::VERTEX);

    GLuint geometryShader{};
    if (containGeometryShader)
    {
        const char* geometrySourceCode = geometry.c_str();
        geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryShader, 1, &geometrySourceCode, nullptr);
        glCompileShader(geometryShader);
        ErrorHandling(geometryShader, shaderType::GEOMETRY);
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertShader);
    glAttachShader(m_ID, fragShader);
    if (containGeometryShader)
        glAttachShader(m_ID, geometryShader);

    glLinkProgram(m_ID);
    ErrorHandling(m_ID, shaderType::PROGRAM);

    glDeleteShader(fragShader);
    glDeleteShader(vertShader);
    if (geometryShader)
        glDeleteShader(geometryShader);
}



