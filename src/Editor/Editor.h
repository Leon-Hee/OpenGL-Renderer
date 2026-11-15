#pragma once
#include "GLFW/glfw3.h"

class Editor
{
private:
    
public:
    Editor();
    ~Editor();

    void Init(GLFWwindow *window);
    void BeginFrame();
    void Draw();
    void EndFrame();
    void Shutdown();
};


