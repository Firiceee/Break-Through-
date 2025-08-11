#include "header/game.h"


SpriteRenderer  *Renderer;

Game::Game(int width, int height):
m_width(width), m_height(height)
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
    Renderer->Draw(ResourceManager::GetTexture("face"),
        glm::vec2(200.0f, 200.0f),
        glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    glfwSwapBuffers(windowManager.getWindow());
    glfwPollEvents();
}

void Game::Update(GLfloat deltaTime)
{

}
Game::~Game()
{
    delete Renderer;
    ResourceManager::Clear();
}


bool Game::shouldClose()
{
    return glfwWindowShouldClose(windowManager.getWindow());
}

void Game::Init()
{
    // Set game pointer in window manager for callback access
    windowManager.setGamePointer(this);
    
    // load shaders
    ResourceManager::LoadShader("resources/shader/def.vert", "resources/shader/def.frag", "", "sprite");
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
        static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader("sprite").Use().SetInt("tex", 0);
    ResourceManager::GetShader("sprite").SetMat4("projection", projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
    Renderer->initRenderData();
    // load textures
    ResourceManager::LoadTexture("resources/texture/awesomeface.png", false,
        GL_REPEAT, GL_REPEAT,
        GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, "face");
}
