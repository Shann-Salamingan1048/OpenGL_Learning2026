cmake_minimum_required(VERSION 3.28)
project(OpenGL_Learning2026 C CXX)

# --- 1. C++23 CONFIGURATION ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Force GCC to enable module support
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fmodules-ts)
endif()
# --- 2. INCLUDE DIRECTORIES ---
set(SOURCE_FILES
        main.cpp
        core/src/glad.c
        stb.cpp
)
# --- 4. CREATE EXECUTABLE ---
add_executable(OpenGL_Learning2026 ${SOURCE_FILES})
# --- 5. ATTACH C++ MODULES ---
target_sources(OpenGL_Learning2026
        PUBLIC
        FILE_SET CXX_MODULES FILES
        GettingStarted.cppm
        Texture.cppm
        Camera.cppm
        Shader.cppm
        vao.cppm
        vbo.cppm
        ebo.cppm
        TimeUtils.cppm
        Lighting.cppm

        PRIVATE
        GettingStarted.cpp
        Texture.cpp
        Camera.cpp
        Shader.cpp
        vao.cpp
        vbo.cpp
        ebo.cpp

)
target_include_directories(OpenGL_Learning2026 PRIVATE ${CMAKE_SOURCE_DIR}/core/include)
# --- 5. ASSET COPYING (Shaders & Textures) ---
# This handles copying your folders to the build directory so the app can find them
set(ASSET_FOLDERS "glsl" "pics")

foreach(FOLDER ${ASSET_FOLDERS})
    add_custom_command(
            TARGET OpenGL_Learning2026 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/${FOLDER}
            $<TARGET_FILE_DIR:OpenGL_Learning2026>/${FOLDER}
            COMMENT "Syncing ${FOLDER} to build directory..."
    )
endforeach()

# --- 6. PLATFORM-SPECIFIC LINKING ---
if(WIN32)
    # Windows-specific libraries and local GLFW .lib
    target_link_libraries(OpenGL_Learning2026
            PRIVATE
            "${CMAKE_SOURCE_DIR}/core/lib/glfw3.lib"
            opengl32
            gdi32
            user32
            shell32
    )
else()
    # Zorin OS / Linux native libraries
    # IMPORTANT: Run 'sudo apt install libglfw3-dev libgl1-mesa-dev' first!
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
    find_package(OpenGL REQUIRED)

    target_link_libraries(OpenGL_Learning2026
            PRIVATE
            ${GLFW_LIBRARIES}
            OpenGL::GL
            dl # Required for GLAD to load functions at runtime
    )
endif()