#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H
#include <map>
#include <string_view>
#include "shader.h"
#include "texture.h"
#include "glad/glad.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

class ResourceManager
{
public:
    static Shader& LoadShader(const std::string& vertPath, const std::string& fragPath, const std::string& geometryPath, const std::string& name);
    static Texture& LoadTexture(const char* file, bool alpha, GLuint wrapS, GLuint wrapT, GLuint minFilter, GLuint magFilter, const std::string& name);
    static Shader& GetShader(const std::string& name);
    static Texture& GetTexture(const std::string& name);
    static void Clear();
private:
    static std::map<std::string, Texture> s_textures;
    static std::map<std::string, Shader> s_shaders;
};

#endif