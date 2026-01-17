//
// Created by USER on 1/11/2026.
//

#include "GettingStarted.h"

using namespace GettingStarted;
// Force usage of high-performance GPU on Windows


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
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
    {
        std::println("Failed to initialize GLAD");
        return;
    }
}
void GetStart::framebuffer_size_callback(GLFWwindow* window, int width, int height) noexcept
{
    glViewport(0, 0, width, height);
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
