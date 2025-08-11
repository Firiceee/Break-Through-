#include "header/windowmanager.h"

#include <iostream>

void callBackSize(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}


WindowManager::WindowManager()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    m_window = glfwCreateWindow(Constant::Screen::WIDTH, Constant::Screen::HEIGHT,
        Constant::Screen::NAME,nullptr, nullptr);

    glfwMakeContextCurrent(m_window);
    int currWidth, currHeight;
    glfwGetFramebufferSize(m_window, &currWidth, &currHeight);
    gladLoadGL();
    glViewport(0,0,currWidth,currHeight);
    glfwSetFramebufferSizeCallback(m_window, callBackSize);
    m_height = currHeight;
    m_width = currWidth;
}

WindowManager::~WindowManager()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
