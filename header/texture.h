#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

class Texture
{
public:
    Texture(GLuint wrapS, GLuint wrapT, GLuint magFilter, GLuint minFilter);
    ~Texture();
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    // Allow move operations
    Texture(Texture&& other) noexcept;

    Texture& operator=(Texture&& other) noexcept;

    void Generate(GLuint width, GLuint height,GLuint format, GLuint internalFormat ,const unsigned char* data);
    void Bind(GLuint textureNumber);
private:
    GLuint m_ID{};
    GLuint m_width{};
    GLuint m_height{};
    GLuint m_wrapS{};
    GLuint m_wrapT{};
    GLuint m_magFilter{};
    GLuint m_minFilter{};
    GLuint m_format{};
    GLuint m_internalFormat{};

};

#endif
