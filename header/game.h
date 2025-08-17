#ifndef GAME_H
#define GAME_H
#include "windowmanager.h"
#include "gamelevel.h"
#include "resource_manager.h"
#include "spriteRenderer.h"
#include "ball.h"
#include "shader.h"
#include "particuleGenerator.h"
#include <glad/glad.h>
#include <vector>


enum class GameState
{
    GAME_ACTIVE, GAME_MENU, GAME_WIN
};

class Game
{
public:
    Game(int width, int height);
    ~Game();
    void Init();
    Game(Game& g) = delete;
    Game& operator=(Game&) = delete;
    void ProcessInput(GLfloat deltaTime);
    void Update(GLfloat deltaTime, float time);
    void Render();
    bool shouldClose();
    WindowManager windowManager{};
    // With Option B we keep internal width/height constant during a level
    void setSize(int width, int height) { m_width = width; m_height = height; }
    
private:
    GameState m_state{GameState::GAME_ACTIVE};
    GameObject m_player{};
    Ball m_ball{};
    ParticuleGenerator m_particles{};
    int m_width{};
    int m_height{};
    std::vector<GameLevel> m_levels;
    int m_currentLevel{1};
    bool                    m_Keys[1024];

};

#endif