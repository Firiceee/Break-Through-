#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "spriteRenderer.h"
#include "texture.h"

class GameLevel;

class GameObject
{
public:
    GameObject() = default;
    GameObject(glm::vec2 position, glm::vec2 size, Texture* sprite,
        glm::vec3 color = glm::vec3(1.0f), glm::vec2 velocity = glm::vec2(0.0f, 0.0f));
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer);

private:
    bool m_IsSolid{};
    glm::vec2 m_size{};
    glm::vec2 m_position{};
    glm::vec2 m_velocity{};
    glm::vec3 m_color{};
    GLfloat m_rotate{};
    Texture* m_texture{};
    bool m_destroyed{};

    friend GameLevel;
};

#endif