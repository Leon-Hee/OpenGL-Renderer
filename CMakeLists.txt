cmake_minimum_required(VERSION 3.20)

project(LeonsRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 3.5 REQUIRED)
find_library(OPENGL_FRAMEWORK OpenGL REQUIRED)

add_executable(
    LeonsRenderer
    src/main.cpp
    src/Core/Application.cpp
    src/Core/Window.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/Resources/VertexBuffer.cpp
)

target_link_libraries(LeonsRenderer PRIVATE 
    glfw
    ${OPENGL_FRAMEWORK}
)