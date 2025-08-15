#ifndef PARTICULE_GENERATOR_H
#define PARTICULE_GENERATOR_H
#include <glm/glm.hpp>
#include "constant.h"
#include <array>

struct Particule
{
    glm::vec2 pos, velocity;
    glm::vec4 color;
    float life;
    Particule():
    pos(0.0f), velocity(0.0f), color(1.0f), life(Constant::Particule::LIFETIME)
    {
    }
};

class ParticuleGenerator
{
public:
    // return the index of a dead Particule
    int indexDeadParticule();
    void Regenerate();

private:
    std::array<Particule, Constant::Particule::MAX_NUMBER_OF_PARTICULE> particules;
    int newPerFrame {Constant::Particule::NEW_PER_FRAME};
    int lastRemoved {};

};

#endif