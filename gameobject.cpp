#include "header/gameobject.h"

void GameObject::Draw(SpriteRenderer& renderer)
{
    renderer.Draw(*m_texture,m_position, m_size, m_rotate, m_color);
}
GameObject::GameObject(glm::vec2 position, glm::vec2 size, Texture* sprite, glm::vec3 color, glm::vec2 velocity):
m_position(position), m_size(size), m_texture(sprite), m_color(color), m_velocity(velocity)
{

}

