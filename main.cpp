#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "header/shader.h"
#include "header/constant.h"
#include "header/game.h"

int main()
{
    Game game{};

    GLfloat timer{};
    GLfloat deltatime{};
    while (! game.shouldClose())
    {
        deltatime = static_cast<float>(glfwGetTime()) - timer;
        timer = static_cast<float>(glfwGetTime());
        game.ProcessInput(deltatime);
        game.Update(deltatime);
        game.Render();
    }
    return 0;
}

