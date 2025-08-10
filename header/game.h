#ifndef GAME_H
#define GAME_H
#include <glad/glad.h>

enum class GameState
{
    GAME_ACTIVE, GAME_MENU, GAME_WIN
};

class Game
{
public:
    Game(GLuint width, GLuint height);
    ~Game();
    Game(Game& g) = delete;
    Game& operator=(Game&) = delete;
    void ProcessInput(GLfloat deltaTime);
    void Update(GLfloat deltaTime);
    void Render();
private:
    GameState m_state;
    bool                    m_Keys[1024];
    unsigned int            m_width, m_height;

};

#endif