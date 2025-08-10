#include "header/resource_manager.h"


void ResourceManager::Clear()
{
    for (auto& pair : s_textures )
    {
        ResourceManager::GetTexture(pair.first).Delete();
    }
    for (auto& pair : s_shaders )
    {
        ResourceManager::GetShader(pair.first).Delete();
    }
}

Shader& ResourceManager::GetShader(const std::string& name)
{
    return s_shaders.at(name);
}

Texture& ResourceManager::GetTexture(const std::string& name)
{
    return s_textures.at(name);
}

Shader& ResourceManager::LoadShader(const std::string& vertPath, const std::string& fragPath,
                                  const std::string& geometryPath, const std::string& name)
{
    auto [iterator, inserted] = s_shaders.try_emplace(
        name,vertPath, fragPath, geometryPath);

    return iterator->second;
}

Texture& ResourceManager::LoadTexture(const char* file, bool alpha, GLuint wrapS,GLuint wrapT,GLuint minFilter,
    GLuint magFilter,const std::string& name)
{
    auto [iterator, inserted] = s_textures.try_emplace(name, wrapS, wrapT, magFilter, minFilter);
    Texture& tex = iterator->second;
    GLuint internalFormat = alpha? GL_RGBA : GL_RGB;
    int width, height, nummChan;
    unsigned char* data = stbi_load(file, &width, &height, &nummChan,0);
    if (!data)
    {
        std::cerr << "Could not load the file " << file << std::endl;
        throw std::runtime_error("Failed to load the file");
    }
    GLuint format = nummChan == 4 ? GL_RGBA : GL_RGB;
    tex.Generate(width, height, format, internalFormat, data);
    stbi_image_free(data);
    return tex;

}
