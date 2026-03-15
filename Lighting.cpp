
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

void Lightings::tryLightCube()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    Shader lightingShader("glsl/lighting/1.color.vert", "glsl/lighting/1.color.frag");
    Shader lightCubeShader("glsl/lighting/1.light_cube.vert", "glsl/lighting/1.light_cube.frag");
    VAO CubeVao;
    VBO vbo(vertices, sizeof(vertices));

    CubeVao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    VAO lightCubeVao;
    lightCubeVao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
    while (!isWindowRunning())
    {
        // Time
        time.currentFrame = static_cast<float>(glfwGetTime());
        time.deltaTime = time.currentFrame - time.lastFrame;
        time.lastFrame = time.currentFrame;

        processInput(m_window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f,0.5f,0.31f);
        lightingShader.setVec3("lightColor", 1.0f,1.0f,1.0f);
        // create transformations

        // view/projection transformations
        auto projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height) , 0.01f, 100.0f);
        auto view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        auto model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);
        // pass them to the shaders (3 different ways)
        CubeVao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lightCubeShader.setMat4("model", model);

        lightCubeVao.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    CubeVao.Delete();
    lightCubeVao.Delete();
    vbo.Delete();
    lightCubeShader.deleteShader();
    lightingShader.deleteShader();
    glfwTerminate();
}

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