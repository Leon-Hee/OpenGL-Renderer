#include <GLFW/glfw3.h>

class Window
{
private:
    GLFWwindow* m_Window;
public:
    Window();
    ~Window();

    void PollEvents();
    void SwapBuffers();

    GLFWwindow* GetNativeWindow();
    bool ShouldClose();
};


