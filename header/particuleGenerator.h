#ifndef PARTICULE_GENERATOR_H
#define PARTICULE_GENERATOR_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "constant.h"
#include "shader.h"
#include <array>
#include <glad/glad.h>

struct Particule
{
    glm::vec2 pos, velocity;
    glm::vec4 color;
    float life;
    Particule():
    pos(0.0f), velocity(0.0f), color(1.0f), life(Constant::Particule::LIFETIME)
    {
    }
};

class ParticuleGenerator
{
public:
    ParticuleGenerator();
    ~ParticuleGenerator();
    
    // Update particles and generate new ones
    void Update(float deltaTime, glm::vec2 position, int newParticles = Constant::Particule::NEW_PER_FRAME);
    
    // Draw all live particles
    void Draw(Shader& shader);
    
    // return the index of a dead Particule
    int indexDeadParticule();
    
    // Regenerate a particle at given index and position
    void Regenerate(int index, glm::vec2 position);

private:
    void initRenderData();
    
    std::array<Particule, Constant::Particule::MAX_NUMBER_OF_PARTICULE> particules;
    int newPerFrame {Constant::Particule::NEW_PER_FRAME};
    int lastRemoved {};
    
    // Rendering data
    GLuint m_VAO, m_VBO;

};

#endif