#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>
#include "windowmanager.h"
enum class GameState
{
    GAME_ACTIVE, GAME_MENU, GAME_WIN
};

class Game
{
public:
    Game();
    ~Game();
    Game(Game& g) = delete;
    Game& operator=(Game&) = delete;
    void ProcessInput(GLfloat deltaTime);
    void Update(GLfloat deltaTime);
    void Render();
    bool shouldClose();
    WindowManager windowManager{};
private:
    GameState m_state{GameState::GAME_MENU};
    bool                    m_Keys[1024];

};

#endif