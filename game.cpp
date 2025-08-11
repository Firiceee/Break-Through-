#include "header/game.h"
#include "header/constant.h"


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
    m_levels[m_currentLevel - 1].Draw(*Renderer);
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
    
    // Set up size callback to avoid circular dependency
    windowManager.setSizeCallback(Game::handleResize);
    
    // load shaders
    ResourceManager::LoadShader(Constant::Path::DEF_VERT, Constant::Path::DEF_FRAG, "", Constant::Resource::SPRITE_SHADER);
    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(m_width),
        static_cast<float>(m_height), 0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader(Constant::Resource::SPRITE_SHADER).Use().SetInt(Constant::Resource::TEX_UNIFORM, 0);
    ResourceManager::GetShader(Constant::Resource::SPRITE_SHADER).SetMat4(Constant::Resource::PROJECTION_UNIFORM, projection);
    // set render-specific controls
    Renderer = new SpriteRenderer(ResourceManager::GetShader(Constant::Resource::SPRITE_SHADER));
    Renderer->initRenderData();
    // load textures
    ResourceManager::LoadTexture(Constant::Path::BLOCK_TEXTURE, false,
        GL_REPEAT, GL_REPEAT,
        GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, Constant::Resource::BRICK_TEXTURE);

    ResourceManager::LoadTexture(Constant::Path::BLOCK_SOLID_TEXTURE, false,
    GL_REPEAT, GL_REPEAT,
    GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, Constant::Resource::SOLID_BRICK_TEXTURE);

    m_levels.emplace_back(Constant::Path::LEVEL_1, m_width, m_height);

}

void Game::handleResize(int width, int height)
{
    // Get the game instance from the window user pointer
    GLFWwindow* window = glfwGetCurrentContext();
    if (window) {
        void* gamePtr = glfwGetWindowUserPointer(window);
        if (gamePtr) {
            Game* game = static_cast<Game*>(gamePtr);
            game->setSize(width, height);
        }
    }
}
