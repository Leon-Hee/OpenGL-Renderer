#include "Window.h"
#include <iostream>

Window::Window()
{
    m_Window = nullptr;
    m_Window = glfwCreateWindow(1280, 720, "Leon's Renderer", nullptr, nullptr); // 初始化窗口

    if(!m_Window) {
        std::cout << "Failed to initiate window!" << std::endl;
        return;
    }

    glfwMakeContextCurrent(m_Window);
    
}

Window::~Window()
{
    glfwDestroyWindow(m_Window); // 析构函数摧毁窗口
}

GLFWwindow* Window::GetNativeWindow()
{
    return m_Window;
}

void Window::PollEvents() 
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
    glfwSwapBuffers(m_Window);
}

bool Window::ShouldClose()
{
    return glfwWindowShouldClose(m_Window);
}

void Window::GetFrameBufferSize(int& width, int& height)
{
    glfwGetFramebufferSize(m_Window, &width, &height);
}

void Window::SetShouldClose(bool closed)
{
    if(closed) {
        glfwSetWindowShouldClose(m_Window, GL_TRUE);
    }
    else 
    {
        glfwSetWindowShouldClose(m_Window, GL_FALSE);
    }
}