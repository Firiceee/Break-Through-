#ifndef BALL_H
#define BALL_H
#include "gameobject.h"
#include "constant.h"
#include "resource_manager.h"
#include <functional>

enum class CollisionType {
    None,
    Top,
    Bottom,
    Left,
    Right
};

class Ball : public GameObject
{
public:
    void reset(glm::vec2 position, glm::vec2 velocity);
    Ball();
    float getRadius() const {return m_radius;}
    void init();

    // Collision methods
    CollisionType checkCollision(GameObject& object);
    void manageBrickCollision(GameObject& object, float time);
    void managePaddleCollision(GameObject& object, float time);
    bool checkBorderCollision(float time);
    void normaliseSpeed();
private:
    float m_radius;
    float m_lastHit{};


};


#endif