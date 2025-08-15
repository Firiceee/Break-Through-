#include "header/gamelevel.h"
#include "header/resource_manager.h"
#include "header/constant.h"

void GameLevel::Draw(SpriteRenderer& renderer)
{
    for (auto& brick : m_bricks)
    {
        if (!brick.m_destroyed || brick.m_IsSolid)
        brick.Draw(renderer);
    }

}
bool GameLevel::IsCompleted()
{
    for (auto& brick : m_bricks)
    {
        if (!brick.m_destroyed && !brick.m_IsSolid)
        {
            return false;
        }
    }
    return true;
}


GameLevel::GameLevel(const char* filePath, int width, int height)
{

    m_bricks.clear();
    std::vector<std::vector<int>> toParse  {parseFile(filePath)};
    int numberOfRow = toParse.size();
    int numberOfColumn = toParse[0].size();
    float cellHeight = static_cast<float>(height-Constant::Screen::VOID_SIZE)/(numberOfRow);
    float cellWidth = static_cast<float>(width)/(numberOfColumn);
    glm::vec2 size {cellWidth, cellHeight};
   for (std::size_t i{}; i < numberOfRow; i++)
   {
       for (std::size_t j{}; j < numberOfColumn; j++)
       {
           if (toParse[i][j] == 0)
           {
               continue;;
           }
           glm::vec2 pos {j*cellWidth, i*cellHeight};

           GameObject currentBrick;
           if (toParse[i][j] == 1)
           {
               currentBrick = GameObject(pos, size,&ResourceManager::GetTexture(Constant::Resource::SOLID_BRICK_TEXTURE));
               currentBrick.m_IsSolid = true;
           }
           else if (int colorType = toParse[i][j]; colorType > 1)
           {
           glm::vec3 color{0.2f};
               if (toParse[i][j] == 2)
                   color = glm::vec3(0.2f, 0.6f, 1.0f);
               else if (toParse[i][j] == 3)
                   color = glm::vec3(0.0f, 0.7f, 0.0f);
               else if (toParse[i][j] == 4)
                   color = glm::vec3(0.8f, 0.8f, 0.4f);
               else if (toParse[i][j] == 5)
                   color = glm::vec3(1.0f, 0.5f, 0.0f);
               currentBrick = GameObject(pos, size,&ResourceManager::GetTexture(Constant::Resource::BRICK_TEXTURE), color);
           }
           m_bricks.push_back(currentBrick);
       }
   }
}


std::vector<std::vector<int>> GameLevel::parseFile(const char* filePath)
{
    std::fstream file {filePath};
    if (!file.is_open())
    {
        std::cerr << "Could not open the file " << filePath <<std::endl;
        throw std::runtime_error("Not able to load the file");
    }
    std::vector<std::vector<int>> toParse{};
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<int> newLine;
        for(char c:line)
        {
            if (c >= '0' && c <= '9')
                newLine.push_back(c-'0');
        }
        toParse.push_back(newLine);
    }
    return toParse;
}
