//
// Created by USER on 1/11/2026.
//
module;
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

#include <print>
#include <stb/stb_images.h>
module GettingStarted;
import Shader;
import VAO;
import VBO;
import EBO;
import Texture;
using namespace GettingStarted;
// Force usage of high-performance GPU on Windows
void GetStart::processInput(GLFWwindow *window)
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
void GetStart::mouse_callBack(GLFWwindow* window, double xposIn, double yposIn)
{
    // 1. Retrieve the "GetStart" instance from the window
    GetStart* app = static_cast<GetStart*>(glfwGetWindowUserPointer(window));

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
GetStart::GetStart(uint16_t width, uint16_t height, const char* title)
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
void GetStart::framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept
{
    glViewport(0, 0, width, height);
}
void GetStart::tryMouse()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -5.5f),
        glm::vec3(-0.3f,  1.0f, -15.5f),
    };
    Shader shaderProgram("glsl/gettingStarted/tryMouse.vert", "glsl/gettingStarted/tryMouse.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);

    auto projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height) , 0.01f, 100.0f);
    shaderProgram.setMat4("projection", projection);
    while (!isWindowRunning())
    {
        // Time
        time.currentFrame = static_cast<float>(glfwGetTime());
        time.deltaTime = time.currentFrame - time.lastFrame;
        time.lastFrame = time.currentFrame;

        processInput(m_window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shaderProgram.use();
        // create transformations
        auto view = camera.GetViewMatrix();

        shaderProgram.setMat4("view", view);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        for (uint8_t i = 1; auto& cubePos : cubePositions)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            float angle = glfwGetTime() * 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES,0, 36);
            ++i;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::tryCamera()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -5.5f),
        glm::vec3(-0.3f,  1.0f, -15.5f),
    };
    Shader shaderProgram("glsl/gettingStarted/tryCamera.vert", "glsl/gettingStarted/tryCamera.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);

    auto projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height) , 0.01f, 100.0f);
    shaderProgram.setMat4("projection", projection);
    while (!isWindowRunning())
    {
        // Time
        time.currentFrame = static_cast<float>(glfwGetTime());
        time.deltaTime = time.currentFrame - time.lastFrame;
        time.lastFrame = time.currentFrame;

        processInput(m_window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shaderProgram.use();
        // create transformations
        auto view = camera.GetViewMatrix();

        shaderProgram.setMat4("view", view);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        for (uint8_t i = 0; auto& cubePos : cubePositions)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            float angle = 20.0f * i;
            if (i % 3 == 0)
                angle = glfwGetTime() * 25.0f;

            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES,0, 36);
            ++i;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::walkAround()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -5.5f),
        glm::vec3(-0.3f,  1.0f, -15.5f),
    };
    Shader shaderProgram("glsl/gettingStarted/walkAround.vert", "glsl/gettingStarted/walkAround.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);



    while (!isWindowRunning())
    {
        time.currentFrame = static_cast<float>(glfwGetTime());
        time.deltaTime = time.currentFrame - time.lastFrame;
        time.lastFrame = time.currentFrame;
        processInput(m_window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shaderProgram.use();
        // create transformations
        auto projection    = glm::mat4(1.0f);
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        auto view  = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0,0.0,0.0), glm::vec3(0.0,1.0,0.0));
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height) , 0.01f, 100.0f);
        // retrieve the matrix uniform locations
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        for (uint8_t i = 0; auto& cubePos : cubePositions)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES,0, 36);
            ++i;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::make3rdContainerRotate()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -5.5f),
        glm::vec3(-0.3f,  1.0f, -15.5f),
    };
    Shader shaderProgram("glsl/gettingStarted/make3rdContainerRotate.vert", "glsl/gettingStarted/make3rdContainerRotate.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);



    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shaderProgram.use();
        // create transformations
        auto view          = glm::mat4(1.0f);
        auto projection    = glm::mat4(1.0f);
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        projection = glm::perspective(glm::radians(45.0f), static_cast<float>(m_width) / static_cast<float>(m_height) , 0.01f, 100.0f);
        // retrieve the matrix uniform locations
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        for (uint8_t i = 0; auto& cubePos : cubePositions)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            float angle = 20.0f * i;
            if (i % 3 == 0)
                angle = glfwGetTime() * 25.0f;

            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES,0, 36);
            ++i;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::moreCubes()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    Shader shaderProgram("glsl/gettingStarted/moreCubes.vert", "glsl/gettingStarted/moreCubes.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);



    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shaderProgram.use();
        // create transformations
        auto view          = glm::mat4(1.0f);
        auto projection    = glm::mat4(1.0f);
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        for (uint8_t i = 0; auto& cubePos : cubePositions)
        {
            auto model = glm::mat4(1.0f);
            model = glm::translate(model, cubePos);
            float angle = 20.0f * i;
            model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
            shaderProgram.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES,0, 36);
            ++i;
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::more3d()
{
    glEnable(GL_DEPTH_TEST);
    printCurrentUseGPU();
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    Shader shaderProgram("glsl/gettingStarted/more3d.vert", "glsl/gettingStarted/more3d.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);



    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        shaderProgram.use();
        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        glDrawArrays(GL_TRIANGLES,0, 36);


        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::going3d()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions                   // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/going3d.vert", "glsl/gettingStarted/going3d.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);



    while (!isWindowRunning())
    {
        auto trans = glm::mat4(1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));


        shaderProgram.use();
        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        shaderProgram.setMat4("model", model);
        shaderProgram.setMat4("view", view);
        shaderProgram.setMat4("projection", projection);
        // pass them to the shaders (3 different ways)
        vao.Bind();
        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);


        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::DrawSecondContrainerViaTransformations()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions                   // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/DrawSecondContrainerViaTransformations.vert", "glsl/gettingStarted/DrawSecondContrainerViaTransformations.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);



    while (!isWindowRunning())
    {
        auto trans = glm::mat4(1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));

        shaderProgram.setMat4("transform", trans);
        shaderProgram.use();
        vao.Bind();
        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scale = static_cast<float>(sin(glfwGetTime()));
        trans = glm::scale(trans, {scale, scale, scale} );
        shaderProgram.setMat4("transform", trans);
        shaderProgram.use();
        vao.Bind();
        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();

    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTextureExchangeTranslateAndRotating()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions                   // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTextureExchangeTranslateAndRotating.vert", "glsl/gettingStarted/containerWithAwesomeFaceTextureExchangeTranslateAndRotating.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);


    auto trans = glm::mat4(1.0f);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::translate(trans, glm::vec3(-0.5f, -0.5f, 0.0f));

        shaderProgram.setMat4("transform", trans);
        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        trans = glm::mat4(1.0f);
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTextureRotating()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions                   // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTextureRotating.vert", "glsl/gettingStarted/containerWithAwesomeFaceTextureRotating.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 5 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);


    auto trans = glm::mat4(1.0f);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
        shaderProgram.setMat4("transform", trans);
        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
        trans = glm::mat4(1.0f);
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTextureUniformMix3rdPara()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTextureUniformMix3rdPara.vert", "glsl/gettingStarted/containerWithAwesomeFaceTextureUniformMix3rdPara.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);
    shaderProgram.setFloat("mixThirdPara", 0.5);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTextureDisplayCenterPixel()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions          // colors           // texture coords (note that we changed them to 'zoom in' on our texture image)
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.55f, 0.55f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   0.55f, 0.45f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.45f, 0.45f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.45f, 0.55f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTextureDisplayCenterPixel.vert", "glsl/gettingStarted/containerWithAwesomeFaceTextureDisplayCenterPixel.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    text1.setFilterTexture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    text1.setFilterMipMap(GL_NEAREST, GL_NEAREST);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    text2.setFilterTexture(GL_REPEAT, GL_REPEAT);
    text2.setFilterMipMap(GL_NEAREST, GL_NEAREST);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTexture4Smiley()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTexture4Smiley.vert", "glsl/gettingStarted/containerWithAwesomeFaceTexture4Smiley.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    text1.setFilterTexture(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    text1.setFilterMipMap(GL_LINEAR, GL_LINEAR);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    text2.setFilterTexture(GL_REPEAT, GL_REPEAT);
    text2.setFilterMipMap(GL_LINEAR, GL_LINEAR);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTextureLookReverse()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTextureLookReverse.vert", "glsl/gettingStarted/containerWithAwesomeFaceTextureLookReverse.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerWithAwesomeFaceTexture1()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/containerWithAwesomeFaceTexture1.vert", "glsl/gettingStarted/containerWithAwesomeFaceTexture1.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture
    std::string container = "pics/gettingstarted/container.jpg";
    std::string awesomeFace = "pics/gettingstarted/awesomeface.png";
    Texture text1(container.c_str(),GL_TEXTURE_2D ,GL_TEXTURE0,GL_UNSIGNED_BYTE, true);
    Texture text2(awesomeFace.c_str(),GL_TEXTURE_2D ,GL_TEXTURE1,GL_UNSIGNED_BYTE, true);
    shaderProgram.use();
    shaderProgram.setInt("texture1",0);
    shaderProgram.setInt("texture2",1);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,nullptr);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    text1.Delete();
    text2.Delete();
    glfwTerminate();
}
void GetStart::containerTexture1()
{
    printCurrentUseGPU();
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
   };
    GLuint indices[] =
    {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    Shader shaderProgram("glsl/gettingStarted/container1.vert", "glsl/gettingStarted/container1.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    // Texture

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int width, height, nrChannels;

    std::string imagePath = "pics/gettingstarted/container.jpg";
    unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &nrChannels,0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::println("Failed to load Texture!");
    }
    stbi_image_free(data);//free memory

    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindTexture(GL_TEXTURE_2D, texture);
        shaderProgram.use();
        vao.Bind();

        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    ebo.Delete();
    shaderProgram.deleteShader();
    glfwTerminate();
}
void GetStart::outputVerPostoFrag()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };
    // Much cleaner and less prone to errors
    Shader shaderProgram("glsl/gettingStarted/vertPosToFrag.vert", "glsl/gettingStarted/xOffset.frag");
    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    vao.LinkAttrib(vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

    vao.Unbind();
    vbo.Unbind();

    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        shaderProgram.use();
        vao.Bind();
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    vao.Delete();
    vbo.Delete();
    shaderProgram.deleteShader();
    glfwTerminate();
}
void GetStart::XOffset()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };
    // Much cleaner and less prone to errors
    Shader shaderProgram("glsl/gettingStarted/xOffset.vert", "glsl/gettingStarted/xOffset.frag");

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    float xOFFSET = 0.01f;
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shaderProgram.setFloat("Xoffset", xOFFSET);
        xOFFSET += 0.01f;
        shaderProgram.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    shaderProgram.deleteShader();
    glfwTerminate();
}
void GetStart::UpSideDownTriangle()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;

            out vec3 ourColor;
            void main() {
                gl_Position = vec4(aPos.x, -aPos.y, aPos.z, 1.0);
                // gl_Position = vec4(-aPos, 1.0);
                ourColor = aColor;
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            in vec3 ourColor;
            void main() {
                FragColor = vec4(ourColor, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
void GetStart::TriangleRainbow()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        // positions         // colors
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
   };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;

            out vec3 ourColor;
            void main() {
                gl_Position = vec4(aPos, 1.0);
                ourColor = aColor;
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            in vec3 ourColor;
            void main() {
                FragColor = vec4(ourColor, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
void GetStart::TriangleChangingColor()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            uniform vec4 ourColor;
            void main() {
                FragColor = ourColor;
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f); // location , rgba


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
void GetStart::HelloTriangleExer3()
{
    printCurrentUseGPU();
    GLfloat firstTriangle[] =
    {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f,  0.0f, 0.0f
    };
    GLfloat secondTriangle[] =
    {
        0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, 0.0f,
        1.0f,  0.0f, 0.0f
    };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    const char* orangeShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";
    const char* yellowShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint orangeShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(orangeShader, 1, &orangeShaderSource, nullptr);
    glCompileShader(orangeShader);
    GLuint yellowShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellowShader, 1, &yellowShaderSource, nullptr);
    glCompileShader(yellowShader);

    GLuint orangeShaderProgram = glCreateProgram();
    glAttachShader(orangeShaderProgram, vertexShader);
    glAttachShader(orangeShaderProgram, orangeShader);
    glLinkProgram(orangeShaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(orangeShader);

    GLuint yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShader);
    glAttachShader(yellowShaderProgram, yellowShader);
    glLinkProgram(yellowShaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(yellowShader);


    GLuint VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);


    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orangeShaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glUseProgram(yellowShaderProgram);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(orangeShaderProgram);
    glDeleteProgram(yellowShaderProgram);
    glfwTerminate();
}
void GetStart::HelloTriangleExer2()
{
    printCurrentUseGPU();
    GLfloat firstTriangle[] =
    {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f,  0.0f, 0.0f
    };
    GLfloat secondTriangle[] =
    {
        0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, 0.0f,
        1.0f,  0.0f, 0.0f
    };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBOs[2], VAOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);


    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}
void GetStart::HelloTriangleExer1()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f,  0.0f, 0.0f,
        0.0f,  0.0f, 0.0f,
        0.5f,  0.5f, 0.0f,
        1.0f,  0.0f, 0.0f,
    };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,6);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void GetStart::HelloSquare()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        -0.5f, 0.5f, 0.0f, // top left
        -0.5f, -0.5f, 0.0f, // bottom left
         0.5f,  -0.5f, 0.0f, // bottom right
         0.5f, 0.5f, 0.0f // top right
    };
    GLuint indices[] =
    {
        0,3,2,
        1,0,2
    };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES,6 ,GL_UNSIGNED_INT,0);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void GetStart::HelloTriangle()
{
    printCurrentUseGPU();
    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    const char* vertexShaderSource =
        R"(
            #version 460 core
            layout (location = 0) in vec3 aPos;
            void main() {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }
        )";
    const char* fragmentShaderSource =
        R"(
            #version 460 core
            out vec4 FragColor;
            void main() {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }
        )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 );
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    while (!isWindowRunning())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 ,3);
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}

void GetStart::printCurrentUseGPU() noexcept
{
    // --- 6. Print System Info (Verify GPU & Version) ---
    std::println("---------------------------------------------");
    std::println("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    std::println("GPU Renderer:   {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER))); // Check if this says NVIDIA/AMD!
    std::println("GLAD Version:   {}.{}", GLVersion.major, GLVersion.minor);
    std::println("---------------------------------------------");
}
