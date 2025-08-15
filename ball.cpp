#include "header/ball.h"




Ball::Ball(){}

void Ball::reset(glm::vec2 position, glm::vec2 velocity)
{
    m_position = Constant::Ball::INITIAL_POSITION;
    m_velocity = Constant::Ball::INITIAL_VELOCITY;
}

CollisionType Ball::checkCollision(GameObject& object)
{
    // Axis-Aligned Bounding Box check
    if (m_position.y < object.m_position.y + object.m_size.y &&
        m_position.y + m_size.y > object.m_position.y &&
        m_position.x < object.m_position.x + object.m_size.x &&
        m_position.x + m_size.x > object.m_position.x)
    {
        object.m_destroyed = true;
        // Calculate overlaps on each side
        float overlapLeft   = (m_position.x + m_size.x) - object.m_position.x;
        float overlapRight  = (object.m_position.x + object.m_size.x) - m_position.x;
        float overlapTop    = (m_position.y + m_size.y) - object.m_position.y;
        float overlapBottom = (object.m_position.y + object.m_size.y) - m_position.y;

        // Determine which axis has the smallest overlap
        float minOverlapX = std::min(overlapLeft, overlapRight);
        float minOverlapY = std::min(overlapTop, overlapBottom);

        if (minOverlapX < minOverlapY) {
            // Collision on X axis
            if (overlapLeft < overlapRight)
                return CollisionType::Left;
            else
                return CollisionType::Right;
        } else {
            // Collision on Y axis
            if (overlapTop < overlapBottom)
                return CollisionType::Top;
            else
                return CollisionType::Bottom;
        }
    }

    // No collision
    return CollisionType::None;
}

void Ball::init()
{
    m_position =Constant::Ball::INITIAL_POSITION;
    m_size = Constant::Ball::SIZE;
    m_texture = &ResourceManager::GetTexture("ball");
    m_color = Constant::Ball::COLOR;
    m_velocity = Constant::Ball::INITIAL_VELOCITY;
    m_radius = Constant::Ball::RADIUS;

}

void Ball::manageBrickCollision(GameObject& object, float time)
{
    if (time - m_lastHit < 0.05)
    {
        return;
    }
   CollisionType type = checkCollision(object);
    switch (type)
    {
    case CollisionType::None:
        return;
        case CollisionType::Left:
        case CollisionType::Right:
            m_velocity.x = -m_velocity.x;
            break;
    case CollisionType::Top:
    case CollisionType::Bottom:
        m_velocity.y = -m_velocity.y;
        break;
    }

    m_lastHit = time;
}

bool Ball::checkBorderCollision(float time)
{
    if (time - m_lastHit < 0.05)
    {
        return false;
    }
    glm::vec2 pos = m_position;
    glm::vec2 size = m_size;
    float left = pos.x;
    float right = left + size.x;
    float top = pos.y;
    if (left < 0 || right > Constant::Screen::WIDTH)
    {
        m_lastHit = time;
        m_velocity = {-m_velocity.x,  m_velocity.y};
        return false;
    }
    if (top < 0)
    {
        m_lastHit = time;
        m_velocity = {m_velocity.x,  -m_velocity.y};
        return false;
    }
    if (top > Constant::Screen::HEIGHT)
    {
        return true;
    }
    return false;
}

void Ball::managePaddleCollision(GameObject& object, float time)
{
    if (time - m_lastHit < 0.05)
    {
        return;
    }
    CollisionType type = checkCollision(object);
    switch (type)
    {
    case CollisionType::None:
        return;
    case CollisionType::Left:
    case CollisionType::Right:
        m_velocity.x = -m_velocity.x;
        break;
    case CollisionType::Top:
    case CollisionType::Bottom:
        m_velocity.y = -m_velocity.y;
        break;
    }
    m_velocity += object.m_velocity;

    m_lastHit = time;
}

void Ball::normaliseSpeed()
{
    m_velocity = Constant::Ball::SPEED*glm::normalize(m_velocity);
    if (m_velocity.y > 0)
    m_velocity = {m_velocity.x, glm::max(m_velocity.y, Constant::Ball::MIN_UP_SPEED)};
    else
        m_velocity = {m_velocity.x, glm::min(m_velocity.y, -Constant::Ball::MIN_UP_SPEED)};
}
