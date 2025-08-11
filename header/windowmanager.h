#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "constant.h"

// Function pointer type for size callback
typedef void (*SizeCallback)(int width, int height);

void callBackSize(GLFWwindow* window, int width, int height);

class WindowManager
{
public:
    WindowManager();
    ~WindowManager();
    GLFWwindow* getWindow(){return  m_window;}
    void setGamePointer(void* gamePtr);
    void setSizeCallback(SizeCallback callback);
private:
    GLFWwindow* m_window{};
    GLuint m_width{};
    GLuint m_height{};
    SizeCallback m_sizeCallback{nullptr};
};

#endif
