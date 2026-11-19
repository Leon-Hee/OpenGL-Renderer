#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Window.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Resources/VertexBuffer.h"
#include "../Renderer/Resources/VertexArray.h"
#include "../Editor/Editor.h"
#include "../Scene/Scene.h"
#include "../Renderer/Resources/Shader.h"
#include "../Renderer/Resources/Texture.h"
#include "../Renderer/Resources/Material.h"
#include "../Renderer/Resources/Mesh.h"
#include "../Renderer/Camera.h"


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

    Editor editor; // Editor 是“运行在 OpenGL 窗口里的 UI”，所以它必须依赖 Window 已经建立好的 OpenGL Context。
    editor.Init(window.GetNativeWindow());

    std::cout << "OpenGL Version: "
          << glGetString(GL_VERSION)
          << std::endl;

    std::cout << "GLSL Version: "
            << glGetString(GL_SHADING_LANGUAGE_VERSION)
            << std::endl;

    std::cout << "Renderer: "
            << glGetString(GL_RENDERER)
            << std::endl;

    Camera camera(1280.0f, 720.0f, 45.0f, 0.1f, 100.0f);
    Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
    Texture texture("../assets/textures/test.jpeg");
    
    Material material(shader, texture);
    


    float vertices[] = {
    -0.5, -0.5, 0.0, 0.0,
    0.5, -0.5, 1.0, 0.0,
    0.0,  0.5, 0.5, 1.0
    };

    VertexBufferLayout vertexBufferLayout;
    vertexBufferLayout.PushFloat(2);
    vertexBufferLayout.PushFloat(2);
    Mesh mesh(vertices, sizeof(vertices), 3, material, vertexBufferLayout);



    
    while(!window.ShouldClose()) 
    {
        window.PollEvents();

        editor.BeginFrame(); 

        renderer.BeginFrame();
        renderer.Clear();

        mesh.Draw();

        editor.Draw();
        editor.EndFrame();

        renderer.EndFrame();
        window.SwapBuffers();
    }
    editor.Shutdown();

}
