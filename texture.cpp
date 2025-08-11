#include "header/texture.h"

void Texture::Bind(GLuint textureNumber)
{
    glActiveTexture(GL_TEXTURE0 + textureNumber);
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

void Texture::Generate(GLuint width, GLuint height,GLuint format, GLuint internalFormat ,const unsigned char* data)
{
    m_width = width;
    m_height = height;
    m_format = format;
    m_internalFormat = internalFormat;
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height,
        0,m_format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(GLuint wrapS, GLuint wrapT, GLuint magFilter, GLuint minFilter):
m_wrapS(wrapS), m_wrapT(wrapT), m_magFilter(magFilter), m_minFilter(minFilter)
{

    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Delete()
{
    glDeleteTextures(1, &m_ID);
}

Texture::~Texture()
{
    Delete();
}

Texture::Texture(Texture&& other) noexcept :m_ID(other.m_ID), m_width(other.m_width), m_height(other.m_height),
      m_format(other.m_format), m_internalFormat(other.m_internalFormat),  // Add this
      m_wrapS(other.m_wrapS), m_wrapT(other.m_wrapT),
      m_magFilter(other.m_magFilter), m_minFilter(other.m_minFilter)
{
    other.m_ID = 0;
}

Texture& Texture::operator=(Texture&& other) noexcept
{

        if (this != &other) {
            // Clean up current resource
            glDeleteTextures(1, &m_ID);

            // Move data
            m_ID = other.m_ID;
            m_width = other.m_width;
            m_height = other.m_height;
            m_format = other.m_format;
            m_wrapS = other.m_wrapS;
            m_wrapT = other.m_wrapT;
            m_magFilter = other.m_magFilter;
            m_minFilter = other.m_minFilter;

            other.m_ID = 0; // Prevent deletion
        }
        return *this;

}
