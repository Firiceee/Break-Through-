#include "header/windowmanager.h"
#include <iostream>

// Global callback function that will be set by the window manager
static SizeCallback g_sizeCallback = nullptr;

void callBackSize(GLFWwindow* window, int width, int height)
{
    // Query actual framebuffer size
    glfwGetFramebufferSize(window, &width, &height);

    // Compute letterboxed viewport based on virtual resolution
    const float virtualAspect = static_cast<float>(Constant::Screen::WIDTH) /
                                static_cast<float>(Constant::Screen::HEIGHT);
    const float windowAspect = static_cast<float>(width) / static_cast<float>(height);

    int vpW, vpH, vpX, vpY;
    if (windowAspect > virtualAspect) {
        // Window is wider than virtual aspect → fit by height
        vpH = height;
        vpW = static_cast<int>(height * virtualAspect);
        vpX = (width - vpW) / 2;
        vpY = 0;
    } else {
        // Window is taller/narrower → fit by width
        vpW = width;
        vpH = static_cast<int>(width / virtualAspect);
        vpX = 0;
        vpY = (height - vpH) / 2;
    }

    glViewport(vpX, vpY, vpW, vpH);

    // Notify optional listeners
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

    // Initialize viewport with correct letterboxing
    callBackSize(m_window, currWidth, currHeight);
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
