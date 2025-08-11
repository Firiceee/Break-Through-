#ifndef SPRITERENDERER_H
#define SPRITERENDERER_H
#include "shader.h"
#include "texture.h"
#include <glm/gtc/matrix_transform.hpp>

class SpriteRenderer
{
public:

    void Draw(Texture& texture, glm::vec2 position, glm::vec2 size={10.f, 10.f},
        float rotate=0, glm::vec3 color={1.f, 1.f, 1.f});
    SpriteRenderer(Shader& shader);
    ~SpriteRenderer();

private:

    Shader m_Shader;
    GLuint m_VAO{};
    GLuint m_VBO{};
    GLuint m_EBO{};

    void initRenderData();
};

#endif