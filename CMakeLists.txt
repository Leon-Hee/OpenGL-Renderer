cmake_minimum_required(VERSION 3.20)

project(LeonsRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.5 REQUIRED)
find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)

add_compile_definitions(GL_SILENCE_DEPRECATION)

add_executable(
    LeonsRenderer
    third_party/imgui/imgui.cpp
    third_party/imgui/imgui_draw.cpp
    third_party/imgui/imgui_tables.cpp
    third_party/imgui/imgui_widgets.cpp
    third_party/imgui/backends/imgui_impl_glfw.cpp
    third_party/imgui/backends/imgui_impl_opengl3.cpp
    
    src/main.cpp
    src/Core/Application.cpp
    src/Core/Window.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Resources/VertexBuffer.cpp
    src/Renderer/Resources/VertexArray.cpp
    src/Editor/Editor.cpp
    src/Scene/Scene.cpp
    src/Scene/Entity.cpp
    src/Renderer/Resources/Shader.cpp

    
    
)

target_include_directories(LeonsRenderer PRIVATE
    third_party/imgui
    third_party/imgui/backends
)

target_link_libraries(LeonsRenderer PRIVATE 
    glfw
    ${OPENGL_FRAMEWORK}
)