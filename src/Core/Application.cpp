#include "Application.h"

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

void Application::ProcessCameraInput(Window& window, Camera& camera, float deltaTime)
{
    float cameraSpeed = 2.5f;

    if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        camera.MoveForward(cameraSpeed * deltaTime);
    }

    if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        camera.MoveForward(-cameraSpeed * deltaTime);
    }

    if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        camera.MoveRight(cameraSpeed * deltaTime);
    }

    if (glfwGetKey(window.GetNativeWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        camera.MoveRight(-cameraSpeed * deltaTime);
    }
}

void Application::MouseCallBack( // // 通过 GLFW 窗口的 UserPointer 将 Camera 对象绑定到鼠标回调，从而在回调中获取 Camera 并处理鼠标视角。
    GLFWwindow* glfwWindow,
    double xPos,
    double yPos
)
{
    Camera* camera =
        static_cast<Camera*>(
            glfwGetWindowUserPointer(glfwWindow)
        );

    if (camera)
    {
        camera->ProcessMouseMovement(
            static_cast<float>(xPos),
            static_cast<float>(yPos)
        );
    }
} 

void Application::ProcessInput(Window& window) {
    if(glfwGetKey(window.GetNativeWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        window.SetShouldClose(true);

    }
}

void Application::Run()
{   
    Window window;
    glfwSetCursorPosCallback(window.GetNativeWindow(), MouseCallBack);
    glfwSetInputMode(
        window.GetNativeWindow(),
        GLFW_CURSOR,
        GLFW_CURSOR_DISABLED
    );


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
        100.0f,
        glm::vec3(0.0f, 0.0f, 3.0f),
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    glfwSetWindowUserPointer(
        window.GetNativeWindow(),
        &camera
    );

    Shader shader(
        "../assets/shaders/basic.vert",
        "../assets/shaders/basic.frag"
    );

    Shader shadowDepthShader(
        "../assets/shaders/shadow_depth.vert",
        "../assets/shaders/shadow_depth.frag"
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


    RenderQueue queue;
    
    Light light(
        LightType::Spot, 
        glm::vec3(1.0f, 1.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, -1.0f), 
        glm::vec3(1.0f), 
        1.0f, 
        1.0f, 
        0.09f, 
        0.032f,
        glm::cos(glm::radians(12.5f)),
        glm::cos(glm::radians(16.5f))
    );

    Camera lightCamera(
        2048.0f,
        2048.0f,
        33.0f,
        0.1f,
        100.0f,
        light.GetPosition(),
        light.GetDirection(),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    float lastFrame = 0.0f;


    ShadowMap shadowMap(2048, 2048);

    ShadowPass shadowPass(shadowMap, shadowDepthShader);


 
    while(!window.ShouldClose()) 
    {
        window.PollEvents();
        ProcessInput(window);

        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessCameraInput(
            window,
            camera,
            deltaTime
        );

        lightCamera.SetPosition(light.GetPosition());
        lightCamera.SetFront(light.GetDirection());
        glm::mat4 lightSpaceMatrix = lightCamera.GetProjectionMatrix() * lightCamera.GetViewMatrix();
        renderer.SetLightSpaceMatrix(lightSpaceMatrix);
        renderer.SetShadowMap(shadowMap.GetDepthTexture());

                
        queue.Clear();

        queue.Submit(mesh, transform2);
        queue.Submit(mesh, transform);

        // shadow pass
        shadowPass.Render(queue, lightSpaceMatrix);


        // main pass
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

        renderer.Execute(queue, camera, light);

        editor.Draw();

        editor.EndFrame();

        renderer.EndFrame();

        window.SwapBuffers();
    }

    editor.Shutdown();
}