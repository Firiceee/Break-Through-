#include "header/game.h"
Game::Game()
{

}

void Game::ProcessInput(GLfloat deltaTime)
{
    if (glfwGetKey(windowManager.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windowManager.getWindow(), true);
    }
}

void Game::Render()
{
    glClearColor(1., 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(windowManager.getWindow());
    glfwPollEvents();
}

void Game::Update(GLfloat deltaTime)
{

}
Game::~Game()
{

}


bool Game::shouldClose()
{
    return glfwWindowShouldClose(windowManager.getWindow());
}
