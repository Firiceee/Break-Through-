#include "header/windowmanager.h"
#include <iostream>

// Global callback function that will be set by the window manager
static SizeCallback g_sizeCallback = nullptr;

void callBackSize(GLFWwindow* window, int width, int height)
{
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    // Call the registered callback if available
    if (g_sizeCallback) {
        g_sizeCallback(width, height);
    }
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
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        throw std::runtime_error("GLAD initialization failed");
    }
    
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

void WindowManager::setGamePointer(void* gamePtr)
{
    glfwSetWindowUserPointer(m_window, gamePtr);
}

void WindowManager::setSizeCallback(SizeCallback callback)
{
    m_sizeCallback = callback;
    g_sizeCallback = callback; // Set the global callback
}
