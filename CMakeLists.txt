cmake_minimum_required(VERSION 3.26)
project(OpenGL_Learning2026 C CXX)

# Setting your preferred standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Include Directories
# This points to your 'core/include' so you can do #include <glad/glad.h>
include_directories(${CMAKE_SOURCE_DIR}/core/include)

# 2. Source Files
# We must compile 'main.cpp' AND 'glad.c' together
set(SOURCE_FILES
        main.cpp
        core/src/glad.c
        GettingStarted.cpp
        GettingStarted.h
        Shader.cpp
)

# 3. Create the Executable
add_executable(OpenGL_Learning2026 ${SOURCE_FILES})

# 4. Linking
# Links your local glfw3.lib and the required Windows system libs
target_link_libraries(OpenGL_Learning2026
        PRIVATE
        "${CMAKE_SOURCE_DIR}/core/lib/glfw3.lib"
        opengl32
        gdi32
        user32
        shell32
)