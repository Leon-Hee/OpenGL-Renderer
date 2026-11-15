#include "Editor.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Init(GLFWwindow *window)
{
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    io.Fonts->AddFontFromFileTTF(
        "/Library/Fonts/Arial Unicode.ttf",
        18.0f,
        nullptr,
        io.Fonts->GetGlyphRangesChineseFull()
    );
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Editor::BeginFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Editor::Draw()
{
    // =========================
    // Main Menu Bar
    // =========================
    ImGui::BeginMainMenuBar();

    if (ImGui::BeginMenu("文件"))
    {
        ImGui::MenuItem("新建");
        ImGui::MenuItem("打开");
        ImGui::MenuItem("保存");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("场景"))
    {
        ImGui::MenuItem("新建场景");
        ImGui::MenuItem("保存场景");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("视图"))
    {
        ImGui::MenuItem("场景层级");
        ImGui::MenuItem("检视器");
        ImGui::MenuItem("统计信息");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("渲染"))
    {
        ImGui::MenuItem("线框模式");
        ImGui::MenuItem("显示网格");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("调试"))
    {
        ImGui::MenuItem("GPU 信息");
        ImGui::MenuItem("渲染统计");
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("帮助"))
    {
        ImGui::MenuItem("关于 Leon's Renderer");
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();


    // =========================
    // Scene Hierarchy
    // =========================
    ImGui::Begin("场景层级");

    if (ImGui::TreeNode("场景"))

    {

        ImGui::BulletText("相机");

        ImGui::BulletText("立方体");

        ImGui::BulletText("灯光");

        ImGui::TreePop();

    }

    ImGui::End();


    // =========================
    // Inspector
    // =========================
    ImGui::Begin("检视器");

    ImGui::Text("立方体");
    ImGui::Separator();

    if (ImGui::CollapsingHeader("变换"))
    {
        static float position[3] = {0.0f, 0.0f, 0.0f};
        static float rotation[3] = {0.0f, 0.0f, 0.0f};
        static float scale[3] = {1.0f, 1.0f, 1.0f};

        ImGui::DragFloat3("位置", position, 0.1f);
        ImGui::DragFloat3("旋转", rotation, 1.0f);
        ImGui::DragFloat3("缩放", scale, 0.1f);
    }

    if (ImGui::CollapsingHeader("材质"))
    {
        ImGui::Text("Shader");
        ImGui::Text("颜色");
    }

    if (ImGui::CollapsingHeader("网格"))
    {
        ImGui::Text("Cube Mesh");
        ImGui::Text("Vertices: 36");
    }

    ImGui::End();


    // =========================
    // Viewport
    // =========================
    ImGui::Begin("视口");

    ImGui::Text("Rendering Viewport");

    ImGui::Separator();

    ImGui::Text("OpenGL 4.1");
    ImGui::Text("Renderer: Apple M5");

    ImGui::End();


    // =========================
    // Status Bar
    // =========================
    ImGui::Begin("状态");

    ImGui::Text("状态：正常");
    ImGui::SameLine();
    ImGui::Text("FPS: 60");

    ImGui::End();
}

void Editor::EndFrame()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Editor::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}