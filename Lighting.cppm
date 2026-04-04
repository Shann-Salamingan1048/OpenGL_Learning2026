module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <print>

export module Lighting;
import Camera;
import Time;

export namespace Lighting
{
    class Lightings
    {
    public:
        explicit Lightings(uint16_t width, uint16_t height, const char* title);
        ~Lightings() = default;
    public:
        void tryLightCube();
        void tryAmbientDiffuse();
        void tryPhong();
        void tryPhongMove();
        void tryPhongMoveShadingInViewSpace();
        void tryGouraud();
        void tryMaterial();
        void tryChangeLightCubeAsWell();
        void tryRealWorldObjects();
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