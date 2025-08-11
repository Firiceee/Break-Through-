#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "constant.h"

void callBackSize(GLFWwindow* window, double width, double height);

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();
    GLFWwindow* getWindow(){return  m_window;}
private:
    GLFWwindow* m_window{};
    GLuint m_width{};
    GLuint m_height{};
};

#endif
