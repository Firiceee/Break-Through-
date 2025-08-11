#ifndef GAME_H
#define GAME_H
#include "windowmanager.h"
#include "gamelevel.h"
#include "resource_manager.h"
#include "spriteRenderer.h"
#include "shader.h"
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
    void Update(GLfloat deltaTime);
    void Render();
    bool shouldClose();
    WindowManager windowManager{};
    void setSize(int width, int height) {m_width = width; m_height = height;}
    
    // Static method for window resize callback
    static void handleResize(int width, int height);
    
private:
    GameState m_state{GameState::GAME_MENU};
    int m_width{};
    int m_height{};
    std::vector<GameLevel> m_levels;
    int m_currentLevel{1};
    bool                    m_Keys[1024];

};

#endif