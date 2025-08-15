#ifndef CONST_BALL_H
#define  CONST_BALL_H

#include <glm/glm.hpp>
#include "screen.h"

namespace Constant
{
    namespace Ball
    {
        constexpr float RADIUS {30};
        constexpr glm::vec2 SIZE {RADIUS, RADIUS};
        constexpr glm::vec2 INITIAL_VELOCITY {30., 150.f};
        constexpr glm::vec2 INITIAL_POSITION {Constant::Screen::WIDTH/2 - RADIUS/2, Constant::Screen::HEIGHT-Constant::Screen::VOID_SIZE/2 - RADIUS/2};
        constexpr glm::vec3 COLOR {1, 0.5, 0.2};
        constexpr float SPEED {250};
        constexpr float MIN_UP_SPEED {190};
    }
}

#endif
