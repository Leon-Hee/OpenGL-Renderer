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
#include "../Renderer/Transform.h"
#include "../Renderer/RenderQueue.h"

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

    Editor editor;

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

    Camera camera(
        1280.0f,
        720.0f,
        45.0f,
        0.1f,
        100.0f
    );

    Shader shader(
        "../assets/shaders/basic.vert",
        "../assets/shaders/basic.frag"
    );

    Texture diffuseTexture(
        "../assets/textures/WallDiffuse.png"
    );
    Texture normalTexture(
        "../assets/textures/WallNormal.png"
    );

    Material material(
        shader,
        diffuseTexture,
        normalTexture
    );

    // 设置为透明物体，进入 Transparent Queue
    material.SetRenderType(RenderType::Opaque);

    Transform transform(
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    Transform transform2(
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    float vertices[] = {

        // Position          UV          Normal          Tangent
        -0.5f, -0.5f,        0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,        1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,        0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f,        1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f
    };

    unsigned int indices[] = {

        0, 1, 2,

        1, 3, 2

    };

    VertexBufferLayout vertexBufferLayout;

    vertexBufferLayout.PushFloat(2);
    vertexBufferLayout.PushFloat(2);
    vertexBufferLayout.PushFloat(3);
    vertexBufferLayout.PushFloat(3);

    Mesh mesh(
        vertices,
        sizeof(vertices),
        material,
        vertexBufferLayout,
        indices,
        sizeof(indices)
    );

    int framebufferwidth = 0;
    int framebufferheight = 0;

    renderer.SetClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );

    // ----------------------------------------
    // RenderQueue 测试
    // ----------------------------------------

    
    

    // ----------------------------------------
    // Main Loop
    // ----------------------------------------
    RenderQueue queue;


    while(!window.ShouldClose()) 
    {
        window.PollEvents();
        
        queue.Clear();

        queue.Submit(mesh, transform2);
        queue.Submit(mesh, transform);



        window.GetFrameBufferSize(
            framebufferwidth,
            framebufferheight
        );

        renderer.SetViewPort(
            0,
            0,
            framebufferwidth,
            framebufferheight
        );

        editor.BeginFrame(); 

        renderer.BeginFrame();

        renderer.SetWireFrame(false);

        renderer.Execute(queue, camera);

        editor.Draw();

        editor.EndFrame();

        renderer.EndFrame();

        window.SwapBuffers();
    }

    editor.Shutdown();
}