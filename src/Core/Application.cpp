#include "Application.h"

Framebuffer* Application::s_Framebuffer = nullptr;
Camera* Application::s_Camera = nullptr;

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

void Application::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    if (width == 0 || height == 0)
    {
        
    }
        return;

    std::cout

        << "Framebuffer Resize: "

        << width

        << " x "

        << height

        << std::endl;

    glViewport(
        0,
        0,
        width,
        height
    );

    if (s_Framebuffer)
    {
        s_Framebuffer->Resize(
            width,
            height
        );
    }

    if (s_Camera)
    {
        s_Camera->SetViewportSize(
            static_cast<float>(width),
            static_cast<float>(height)
        );
    }
}

void Application::SetFramebuffer(Framebuffer* framebuffer)
{
    s_Framebuffer = framebuffer;
}

void Application::SetCamera(Camera* camera)
{
    s_Camera = camera;
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

    int framebufferWidth = 0;
    int framebufferHeight = 0;

    window.GetFrameBufferSize(
        framebufferWidth,
        framebufferHeight
    );

    Camera camera(
        static_cast<float>(framebufferWidth),
        static_cast<float>(framebufferHeight),
        45.0f,
        1.0f,
        200.0f,
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

    Shader screenShader(
        "../assets/shaders/ScreenQuad.vert",
        "../assets/shaders/ScreenQuad.frag"
    );

    Texture diffuseTexture(
        "../assets/textures/WallDiffuse.png"
    );
    Texture normalTexture(
        "../assets/textures/WallNormal.png"
    );

    Texture woodTexture(
        "../assets/textures/Wood.png"
    );

    Material material(
        shader,
        diffuseTexture,
        normalTexture
    );

    Material floorMaterial(
        shader,
        woodTexture,
        normalTexture
    );

    floorMaterial.SetRenderType(RenderType::Opaque);

    

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

    
    Transform floorTransform(
        glm::vec3(0.0f, -0.5f, 0.0f),
        glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 1.0f)
    );

    float vertices[] = {

        // Position              UV          Normal          Tangent
        -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,      0.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
        0.5f,  0.5f, 0.0f,      1.0f, 1.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f, 0.0f
    };
    float floorVertices[] = {

        // Position          UV          Normal          Tangent

        -5.0f, 0.0f, -5.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        5.0f, 0.0f, -5.0f,  5.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        -5.0f, 0.0f,  5.0f,  0.0f, 5.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f,

        5.0f, 0.0f,  5.0f,  5.0f, 5.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f, 0.0f
    };


    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 2
    };

    unsigned int floorIndices[] = {
        0, 2, 1,
        1, 2, 3
    };
    VertexBufferLayout floorLayout;

    floorLayout.PushFloat(3);
    floorLayout.PushFloat(2);
    floorLayout.PushFloat(3);
    floorLayout.PushFloat(3);

    Mesh floorMesh(
        floorVertices,
        sizeof(floorVertices),
        floorMaterial,
        floorLayout,
        floorIndices,
        sizeof(floorIndices)
    );

    VertexBufferLayout vertexBufferLayout;
    

    vertexBufferLayout.PushFloat(3);
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

    

    renderer.SetClearColor(
        0.0f,
        0.0f,
        0.0f,
        1.0f
    );


    RenderQueue queue;
    
    Light light(
        LightType::Spot, 
        glm::vec3(1.5f, 1.5f, 1.5f),
        glm::vec3(-1.0f, -1.0f, -1.0f), 
        glm::vec3(1.0f), 
        1.0f, 
        1.0f, 
        0.09f, 
        0.032f,
        glm::cos(glm::radians(22.5f)),
        glm::cos(glm::radians(25.5f))
    );

    Camera lightCamera(
        2048.0f,
        2048.0f,
        33.0f,
        1.0f,
        100.0f,
        light.GetPosition(),
        light.GetDirection(),
        glm::vec3(0.0f, 1.0f, 0.0f)
    );

    float lastFrame = 0.0f;


    ShadowMap shadowMap(2048, 2048);

    ShadowPass shadowPass(shadowMap, shadowDepthShader);

    MainPass mainPass(renderer);

    
    Framebuffer frameBuffer(framebufferWidth, framebufferHeight);

    SetFramebuffer(&frameBuffer);
    SetCamera(&camera);

    glfwSetFramebufferSizeCallback(
        window.GetNativeWindow(),
        FramebufferSizeCallback
    );

    ScreenQuad screenQuad;
 
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
        const glm::mat4 view = camera.GetViewMatrix();
        const glm::mat4 projection = camera.GetProjectionMatrix();
        
        DrawContext context{
            view,
            projection,
            lightSpaceMatrix, 
            shadowMap.GetDepthTexture(),
            light
        };

                
        queue.Clear();

        queue.Submit(mesh, transform2);
        queue.Submit(mesh, transform);
        queue.Submit(floorMesh, floorTransform);


        // shadow pass
        shadowPass.Render(queue, lightSpaceMatrix);

        frameBuffer.Bind();


        // main pass

        renderer.SetViewPort(
            0,
            0,
            frameBuffer.GetWidth(),
            frameBuffer.GetHeight()
        );

        editor.BeginFrame(); 

        renderer.BeginFrame();

        renderer.Clear();

        renderer.SetWireFrame(false);

        mainPass.Render(queue, camera, context);

        frameBuffer.Unbind();

        
        glDisable(GL_DEPTH_TEST);

        
        screenShader.Bind();

        screenShader.SetInt("screenTexture", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, frameBuffer.GetColorAttachment());

        screenQuad.Draw();

        glEnable(GL_DEPTH_TEST);
        
        

        editor.Draw();

        editor.EndFrame();

        renderer.EndFrame();

        window.SwapBuffers();
    }

    editor.Shutdown();
}