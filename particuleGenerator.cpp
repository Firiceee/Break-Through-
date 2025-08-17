#include "header/particuleGenerator.h"
#include "header/resource_manager.h"
#include "header/constant.h"
#include "header/random.h"
#include <GL/gl.h>

ParticuleGenerator::ParticuleGenerator() 
{
    // Initialize particles array (default constructor of Particule already sets proper values)
    initRenderData();
}

ParticuleGenerator::~ParticuleGenerator()
{
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void ParticuleGenerator::Update(float deltaTime, glm::vec2 position, int newParticles)
{
    // Add new particles
    for (int i = 0; i < newParticles; ++i)
    {
        int deadIndex = indexDeadParticule();
        if (deadIndex != -1)
        {
            Regenerate(deadIndex, position);
        }
    }
    
    // Update all particles
    for (auto& particle : particules)
    {
        particle.life -= deltaTime;
        if (particle.life > 0.0f)
        {
            particle.pos -= particle.velocity * deltaTime;
            particle.color.a = particle.life / Constant::Particule::LIFETIME;
        }
    }
}

void ParticuleGenerator::Draw(Shader& shader)
{
    // Enable blending for particles (additive blending for nice effect)
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    
    for (const auto& particle : particules)
    {
        if (particle.life > 0.0f)
        {
            shader.Use();
            
            // Create model matrix for this particle
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(particle.pos, 0.0f));
            model = glm::scale(model, glm::vec3(10.0f, 10.0f, 1.0f)); // 10x10 pixel particles
            
            shader.SetMat4(Constant::Resource::MODEL_UNIFORM, model);
            shader.SetVec4("color", particle.color);
            
            ResourceManager::GetTexture(Constant::Resource::PARTICLE).Bind();
            glBindVertexArray(m_VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    
    // Reset blending to normal
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

int ParticuleGenerator::indexDeadParticule()
{
    // Search from last removed position for efficiency
    for (int i = lastRemoved; i < Constant::Particule::MAX_NUMBER_OF_PARTICULE; ++i)
    {
        if (particules[i].life <= 0.0f)
        {
            lastRemoved = i;
            return i;
        }
    }
    
    // Search from beginning if not found
    for (int i = 0; i < lastRemoved; ++i)
    {
        if (particules[i].life <= 0.0f)
        {
            lastRemoved = i;
            return i;
        }
    }
    
    // No dead particles found
    lastRemoved = 0;
    return -1;
}

void ParticuleGenerator::Regenerate(int index, glm::vec2 position)
{
    float random = Random::getFloat01() * 100.0f - 50.0f;
    float rColor = 0.5f + Random::getFloat01();
    
    particules[index].pos = position + glm::vec2(random, random);
    particules[index].color = glm::vec4(rColor, rColor, rColor, 1.0f);
    particules[index].life = Constant::Particule::LIFETIME;
    particules[index].velocity = glm::vec2(Random::getFloat01() * 50.0f - 25.0f, Random::getFloat01() * 50.0f - 25.0f);
}

void ParticuleGenerator::initRenderData()
{
    GLuint VBO;
    GLfloat vertices[] = {
        // positions    // texture coords
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position and texture coordinate attributes
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindVertexArray(0);
    m_VBO = VBO;
}