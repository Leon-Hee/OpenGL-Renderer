#include "Application.h"
#include <iostream>
#include <GLFW/glfw3.h>
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


    Shader shader("../assets/shaders/basic.vert", "../assets/shaders/basic.frag");
    Texture texture("../assets/textures/test.jpeg");
    Material material(shader, texture);



    float vertices[] = {
    -0.5, -0.5, 0.0, 0.0,
    0.5, -0.5, 1.0, 0.0,
    0.0,  0.5, 0.5, 1.0
    };

    Mesh mesh(vertices, sizeof(vertices), 3, material);

    Scene scene;

    Entity& camera = scene.CreateEntity("相机");
    Entity& cube = scene.CreateEntity("立方体");
    Entity& light = scene.CreateEntity("光源");

    std::cout << camera.GetID() << " " << camera.GetName() << std::endl;
    std::cout << cube.GetID() << " " << cube.GetName() << std::endl;
    std::cout << light.GetID() << " " << light.GetName() << std::endl;

    
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
