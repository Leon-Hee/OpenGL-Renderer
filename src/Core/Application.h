
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
#include "../Renderer/ShadowMap.h"
#include "../Renderer/ShadowPass.h"

class Application
{
private:
    
public:
    Application();
    ~Application();

    void Run();
    void ProcessCameraInput(Window& window, Camera& camera, float deltaTime);
    static void MouseCallBack(GLFWwindow* glfwWindow, double xPos, double yPos);
    void ProcessInput(Window& window);

};

