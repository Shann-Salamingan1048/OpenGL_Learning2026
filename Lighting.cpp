
module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include <print>
#include <stb/stb_images.h>
module Lighting;
import Shader;
import VAO;
import VBO;
import EBO;
import Texture;

using namespace Lighting;
Lightings::Lightings(uint16_t width, uint16_t height, const char* title)
{
    if (!glfwInit())
    {
        std::println("Failed to initialize GLFW");
        return;
    }
    // Updated to 4.6 to match your GLAD version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (m_window == nullptr)
    {
        std::println("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    glfwGetFramebufferSize(m_window, &m_width, &m_height);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetCursorPosCallback(m_window, mouse_callBack);
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::println("Failed to initialize GLAD");
        return;
    }


    camera.lastX = static_cast<float>(width/2.0f);
    camera.lastY = static_cast<float>(height/2.0f);

}
void Lightings::framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept
{
    glViewport(0, 0, width, height);
}
void Lightings::printCurrentUseGPU() noexcept
{
    // --- 6. Print System Info (Verify GPU & Version) ---
    std::println("---------------------------------------------");
    std::println("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    std::println("GPU Renderer:   {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER))); // Check if this says NVIDIA/AMD!
    std::println("GLAD Version:   {}.{}", GLVersion.major, GLVersion.minor);
    std::println("---------------------------------------------");
}
void Lightings::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraUtils::Camera_Movement::FORWARD, time.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraUtils::Camera_Movement::BACKWARD, time.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraUtils::Camera_Movement::LEFT, time.deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(CameraUtils::Camera_Movement::RIGHT, time.deltaTime);
}
void Lightings::mouse_callBack(GLFWwindow* window, double xposIn, double yposIn)
{
    // 1. Retrieve the "GetStart" instance from the window
    Lightings* app = static_cast<Lightings*>(glfwGetWindowUserPointer(window));

    // Safety check: ensure the pointer isn't null
    if (!app) return;

    // 2. Now use 'app->' to access your member variables
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (app->camera.firstMouse) // Access via app->
    {
        app->camera.lastX = xpos;
        app->camera.lastY = ypos;
        app->camera.firstMouse = false;
    }

    float xoffset = xpos - app->camera.lastX; // Access via app->
    float yoffset = app->camera.lastY - ypos; // Access via app->

    app->camera.lastX = xpos;
    app->camera.lastY = ypos;

    app->camera.ProcessMouseMovement(xoffset, yoffset);
}