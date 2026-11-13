#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "Window.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Resources/VertexBuffer.h"

Application::Application()
{
    if(!glfwInit()) {
        std::cout << "Failed to initiate glfw!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    
}

Application::~Application()
{
    glfwTerminate();
}

void Application::Run()
{   
    Window window;

    Renderer renderer;
    renderer.Init();

    std::cout << "OpenGL Version: "
          << glGetString(GL_VERSION)
          << std::endl;

    std::cout << "GLSL Version: "
            << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;

    std::cout << "Renderer: "
            << glGetString(GL_RENDERER)
            << std::endl;

    float vertices[] = {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.0f,  0.5f
    };

    VertexBuffer vertexbuffer(vertices, sizeof(vertices));
    
    
    while(!window.ShouldClose()) 
    {
        window.PollEvents();
        renderer.BeginFrame();
        renderer.Clear();
        renderer.EndFrame();
        window.SwapBuffers();
    }

}
