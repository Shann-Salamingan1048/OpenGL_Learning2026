cmake_minimum_required(VERSION 3.28)

project(OpenGL_Learning2026 LANGUAGES C CXX)

# --- 1. C++23 CONFIGURATION ---
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    add_compile_options(-fmodules-ts)
endif()

# --- 2. SOURCE FILES ---
set(SOURCE_FILES
        main.cpp
        core/src/glad.c
        stb.cpp
)

set(MODULE_INTERFACE_FILES
        GettingStarted.cppm
        Texture.cppm
        Camera.cppm
        Shader.cppm
        vao.cppm
        vbo.cppm
        ebo.cppm
        TimeUtils.cppm
        Lighting.cppm
)

set(MODULE_IMPLEMENTATION_FILES
        GettingStarted.cpp
        Texture.cpp
        Camera.cpp
        Shader.cpp
        vao.cpp
        vbo.cpp
        ebo.cpp
        Lighting.cpp
)

# --- 3. CREATE EXECUTABLE ---
add_executable(OpenGL_Learning2026)

target_sources(OpenGL_Learning2026
        PRIVATE
        ${SOURCE_FILES}
        ${MODULE_IMPLEMENTATION_FILES}
        PUBLIC
        FILE_SET CXX_MODULES FILES
        ${MODULE_INTERFACE_FILES}
)

target_include_directories(OpenGL_Learning2026
        PRIVATE
        ${CMAKE_SOURCE_DIR}/core/include
)

# --- 4. ASSET SYNC TARGET ---
add_custom_target(sync_assets ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/glsl
        $<TARGET_FILE_DIR:OpenGL_Learning2026>/glsl
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/pics
        $<TARGET_FILE_DIR:OpenGL_Learning2026>/pics
        COMMENT "Syncing shader and texture assets..."
)

add_dependencies(OpenGL_Learning2026 sync_assets)

# --- 5. PLATFORM-SPECIFIC LINKING ---
if(WIN32)
    target_link_libraries(OpenGL_Learning2026
            PRIVATE
            "${CMAKE_SOURCE_DIR}/core/lib/glfw3.lib"
            opengl32
            gdi32
            user32
            shell32
    )
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GLFW REQUIRED glfw3)
    find_package(OpenGL REQUIRED)

    target_include_directories(OpenGL_Learning2026 PRIVATE ${GLFW_INCLUDE_DIRS})
    target_link_directories(OpenGL_Learning2026 PRIVATE ${GLFW_LIBRARY_DIRS})
    target_link_libraries(OpenGL_Learning2026
            PRIVATE
            ${GLFW_LIBRARIES}
            OpenGL::GL
            dl
            pthread
    )
endif()