#include "header/spriteRenderer.h"

void SpriteRenderer::Draw(Texture& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color)
{
    m_Shader.Use();
    // texture
    texture.Bind(0);

    //model
    glm::vec3 translation {position, 0};
    glm::vec3 scaleUp (size, 1);
    glm::mat4 model  {1.f};

    //translation
    model = glm::translate(model, translation);

    //rotation around its center asuming initial scale is (0, 0) (1,1)
    model = glm::translate(model, {size.x *0.5f, size.y*0.5f, 0 });
    model = glm::rotate(model, glm::radians(rotate), {0, 0, 1.f});
    model = glm::translate(model, {-size.x *0.5f, -size.y*0.5f, 0 });

    //scale
    model = glm::scale(model, scaleUp);


    m_Shader.SetMat4("model", model);

    //color
    m_Shader.SetVec3("spriteColor", color);

    // actual draw
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);

}

void SpriteRenderer::initRenderData()
{
    GLuint VAO, VBO, EBO;

    GLfloat vertices[] { 0, 0, 0, 0,
                        1, 0, 1, 0,
                        1, 1, 1, 1,
                        0, 1, 0, 1};

    GLuint indices[] {0, 1, 2, 0,2,3};

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (void*)(0));
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    m_VAO = VAO;
    m_EBO = EBO;
    m_VBO = VBO;

}


SpriteRenderer::SpriteRenderer(Shader& shader):
m_Shader(shader)
{
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteVertexArrays(1, &m_VAO);
}


