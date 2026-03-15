module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <print>

export module GettingStarted;
import Camera;
import Time;

export namespace GettingStarted
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
        ShannUtilities::Time time;
        CameraUtils::Camera camera{glm::vec3(0.0f, 0.0f, 3.0f)};

    private:
        int m_width;
        int m_height;
    };
};
//GettingStarted::GetStart gs(1200,1200, "Getting Started");
//gs.HelloTriangle();
//gs.HelloSquare();
//gs.HelloTriangleExer1();
//gs.HelloTriangleExer2();
//gs.HelloTriangleExer3();
//gs.TriangleChangingColor();
//gs.TriangleRainbow();
//gs.UpSideDownTriangle();
//gs.XOffset();
//gs.outputVerPostoFrag();
//gs.containerTexture1();
//gs.containerWithAwesomeFaceTexture1();
//gs.containerWithAwesomeFaceTextureLookReverse();
//gs.containerWithAwesomeFaceTexture4Smiley();
//gs.containerWithAwesomeFaceTextureDisplayCenterPixel();
//gs.containerWithAwesomeFaceTextureUniformMix3rdPara();
//gs.containerWithAwesomeFaceTextureRotating();
//gs.containerWithAwesomeFaceTextureExchangeTranslateAndRotating();
//gs.DrawSecondContrainerViaTransformations();
//gs.going3d();
//gs.more3d();
//gs.moreCubes();
//gs.make3rdContainerRotate();
//gs.tryCamera();
//gs.walkAround();
//gs.tryMouse();