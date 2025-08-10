#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "header/shader.h"
#include "header/constant.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(Constant::Screen::WIDTH, Constant::Screen::HEIGHT,
        Constant::Screen::NAME, nullptr, nullptr);
    glfwMakeContextCurrent(window);
    int currWidth, currHeight;
    glfwGetFramebufferSize(window, &currWidth, &currHeight);
    gladLoadGL();
    glViewport(0,0,currWidth,currHeight);
    Shader program {Constant::Path::DEF_VERT, Constant::Path::DEF_FRAG};
    glfwTerminate();
    return 0;
}