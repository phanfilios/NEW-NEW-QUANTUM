#pragma once

#include <glm/glm.hpp>

class Camera {
public:
    glm::mat4 viewProjection() const { return glm::mat4(1.0f); }
};
