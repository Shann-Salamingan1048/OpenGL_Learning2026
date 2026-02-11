#pragma once

#include <GLFW/glfw3.h>
#include <print>
#include "TimeUtils.h"
#include "Camera.h"
struct Camera;
struct Time;
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
        void DrawSecondContrainerViaTransformations();
        void going3d();
        void more3d();
        void moreCubes();
        void make3rdContainerRotate();
        void walkAround();
        void tryCamera();
        void tryMouse();

    private:
        GLFWwindow* m_window;
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept;
        bool isWindowRunning() const noexcept{ return glfwWindowShouldClose(m_window);};
        static void printCurrentUseGPU() noexcept;
        void processInput(GLFWwindow *window);
        static void mouse_callBack(GLFWwindow* window, double xpos, double ypos);

    private:
        Time time;
        CameraUtils::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    private:
        int m_width;
        int m_height;
    };
};