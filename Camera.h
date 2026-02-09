#pragma once
#include <glm/glm.hpp>
struct Camera
{
    glm::mat4 view{};
    glm::vec3 pos{};
    glm::vec3 front{};
    glm::vec3 up{};
    glm::vec3 target{};
    glm::vec3 direction{};

    float speed = 2.5f;
};