#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include "gameobject.h"
#include <fstream>
#include <vector>


class GameLevel
{
public:
    void Draw(SpriteRenderer& renderer);
    GameLevel(const char* filePath, int width, int height);
    bool IsCompleted();
private:
    std::vector<GameObject> m_bricks;
    std::vector<std::vector<int>> parseFile(const char* filePath);
};


#endif