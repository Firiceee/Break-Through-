#include "header/game.h"
#include "header/constant.h"


SpriteRenderer  *Renderer;

Game::Game(int width, int height):
m_width(width), m_height(height), m_ball()
{

}

void Game::ProcessInput(GLfloat deltaTime)
{
    if (glfwGetKey(windowManager.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(windowManager.getWindow(), true);
    }
    glm::vec2 speed {0.f};
    if (glfwGetKey(windowManager.getWindow(), GLFW_KEY_A) == GLFW_PRESS )
    {
        speed += glm::vec2(-Constant::Player::SPEED, 0.f);
    }
    if (glfwGetKey(windowManager.getWindow(), GLFW_KEY_D) == GLFW_PRESS )
    {
        speed += glm::vec2(Constant::Player::SPEED, 0.f);
    }
        m_player.changeVelocity(speed);
}

void Game::Render()
{
    glClearColor(0., 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    if(m_state == GameState::GAME_ACTIVE)
    {
        // draw background
        Renderer->Draw(ResourceManager::GetTexture("background"),
            glm::vec2(0.0f, 0.0f), glm::vec2(m_width, m_height), 0.0f
        );
        // draw level
        m_levels[m_currentLevel - 1].Draw(*Renderer);
        m_player.Draw(*Renderer);
        m_ball.Draw(*Renderer);
        
        // Draw particles with their own shader
        m_particles.Draw(ResourceManager::GetShader(Constant::Resource::PARTICLE_SHADER));
    }
    glfwSwapBuffers(windowManager.getWindow());
    glfwPollEvents();
}

void Game::Update(GLfloat deltaTime, float time)
{
    if (m_state==GameState::GAME_ACTIVE)
    {
        m_player.moove(deltaTime);
        m_ball.managePaddleCollision(m_player, time);
        m_ball.checkBorderCollision(time);
        for (auto& brick : m_levels[m_currentLevel-1].getBricks())
        {
            if (!brick.m_destroyed || brick.m_IsSolid)
            m_ball.manageBrickCollision(brick, time);
        }
        m_ball.normaliseSpeed();
        m_ball.moove(deltaTime);
        
        // Update particles at ball position
        m_particles.Update(deltaTime, m_ball.m_position);
    }
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
    
    // Do not mutate internal width/height on resize (Option B).
    // Keep a fixed virtual projection tied to Constant::Screen.
    windowManager.setSizeCallback(nullptr);
    
    // load shaders
    ResourceManager::LoadShader(Constant::Path::DEF_VERT, Constant::Path::DEF_FRAG, "", Constant::Resource::SPRITE_SHADER);
    ResourceManager::LoadShader(Constant::Path::PART_VERT, Constant::Path::PART_FRAG, "", Constant::Resource::PARTICLE_SHADER);
    
    // Enable OpenGL blending for alpha transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // configure shaders with virtual resolution that stays constant during a level
    glm::mat4 projection = glm::ortho(0.0f,
                                      static_cast<float>(Constant::Screen::WIDTH),
                                      static_cast<float>(Constant::Screen::HEIGHT),
                                      0.0f, -1.0f, 1.0f);

    ResourceManager::GetShader(Constant::Resource::SPRITE_SHADER).Use().SetInt(Constant::Resource::TEX_UNIFORM, 0);
    ResourceManager::GetShader(Constant::Resource::SPRITE_SHADER).SetMat4(Constant::Resource::PROJECTION_UNIFORM, projection);
    
    // Configure particle shader
    ResourceManager::GetShader(Constant::Resource::PARTICLE_SHADER).Use().SetInt(Constant::Resource::TEX_UNIFORM, 0);
    ResourceManager::GetShader(Constant::Resource::PARTICLE_SHADER).SetMat4(Constant::Resource::PROJECTION_UNIFORM, projection);
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


    ResourceManager::LoadTexture(Constant::Path::BACKGROUND, false,
    GL_REPEAT, GL_REPEAT,
    GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, Constant::Resource::BACKGROUND);

    ResourceManager::LoadTexture(Constant::Path::BALL, true, GL_REPEAT, GL_REPEAT,
    GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, Constant::Resource::BALL);

    ResourceManager::LoadTexture("resources/texture/particle.png", true, GL_REPEAT, GL_REPEAT,
    GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR, Constant::Resource::PARTICLE);

    // Build level using the same virtual resolution
    m_levels.emplace_back(Constant::Path::LEVEL_1,
                          Constant::Screen::WIDTH,
                          Constant::Screen::HEIGHT);
    ResourceManager::LoadTexture(Constant::Path::PLAYER, false, GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_NEAREST,
        GL_LINEAR, Constant::Resource::PLAYER);

    //initialize player
    m_player =  {{Constant::Screen::MIDDLE_SCREEN - Constant::Player::WIDTH/2,
        Constant::Screen::HEIGHT - Constant::Player::HEIGHT - Constant::Player::SHIFT},
        {Constant::Player::WIDTH, Constant::Player::HEIGHT},
        &ResourceManager::GetTexture(Constant::Resource::PLAYER)};



    m_ball.init();

}

// No resize handler in Option B: we keep a fixed virtual resolution per level
