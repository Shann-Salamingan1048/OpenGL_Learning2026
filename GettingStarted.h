#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <print>
#include <string_view>
#include <string>
#include "Shader.h"
namespace GettingStarted
{
    class GetStart
    {
    public:
        explicit GetStart(uint16_t width, uint16_t height, const char* title);
        ~GetStart() = default;
        void HelloTriangle();
        void HelloSquare();
        void HelloTriangleExer1();
        void HelloTriangleExer2();
        void HelloTriangleExer3();
        void TriangleChangingColor();
        void TriangleRainbow();
        void UpSideDownTriangle();
        void XOffset();
        void outputVerPostoFrag();
    private:
        GLFWwindow* m_window;
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept;
        bool isWindowRunning() const noexcept{ return glfwWindowShouldClose(m_window);};
        static void printCurrentUseGPU() noexcept;

    };
};