#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <print>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string_view>
#include <string>
#include "Shader.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "Texture.h"
#include <stb/stb_images.h>
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
        void containerTexture1();
        void containerWithAwesomeFaceTexture1();
        void containerWithAwesomeFaceTextureLookReverse();
        void containerWithAwesomeFaceTexture4Smiley();
        void containerWithAwesomeFaceTextureDisplayCenterPixel();
        void containerWithAwesomeFaceTextureUniformMix3rdPara();
        void containerWithAwesomeFaceTextureRotating();
        void containerWithAwesomeFaceTextureExchangeTranslateAndRotating();
    private:
        GLFWwindow* m_window;
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept;
        bool isWindowRunning() const noexcept{ return glfwWindowShouldClose(m_window);};
        static void printCurrentUseGPU() noexcept;

    };
};